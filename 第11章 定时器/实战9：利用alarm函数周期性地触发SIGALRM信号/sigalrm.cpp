#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <libgen.h>

#include "lst_timer.h"

#define FD_LIMIT 65535
#define MAX_EVENT_NUMBER 1024
#define TIMESLOT 5

static int pipefd[2];

static sort_timer_lst timer_lst; /* 用升序链表来管理定时器 */
static int epollfd = 0;

/* 将文件描述符设置为非阻塞模式 */
int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/* addfd 函数把新的文件描述符添加到 epoll 监听列表中，
 * 并且设置为非阻塞和边缘触发模式（EPOLLET），以提高事件处理的效率。
 */
void addfd(int epollfd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event); /* 将fd注册到内核事件表epollfd中*/
    setnonblocking(fd);
}

/* sig_handler 用于处理程序接收到的信号。
 * 它把信号编号发送到 pipefd 管道，这样主循环可以安全地处理信号事件。
 * 这种使用信号和管道的组合是多线程或多进程环境中处理信号的一种安全模式。
*/
void sig_handler(int sig) {
    int save_errno = errno;
    int msg = sig;
    // 此处还是老bug，没有考虑字节序就发送了int的低地址的1字节
    send(pipefd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

/* addsig 函数设置信号处理函数，并确保系统调用被中断时能自动重启，避免了部分系统调用失败的问题。 */
void addsig(int sig) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

void timer_handler() {
    // 处理定时任务
    timer_lst.tick();
    // 由于alarm函数只会引起一次SIGALRM信号，因此重新定时，以不断触发SIGALRM信号
    alarm(TIMESLOT);
}

/* 定时器回调函数，它删除非活动连接socket上的注册事件，并关闭之 */ 
void cb_func(client_data *user_data) {
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    printf("close fd %d\n", user_data->sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5); /* 创建内核事件表 */
    assert(epollfd != -1);
    addfd(epollfd, listenfd);

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    setnonblocking(pipefd[1]);  /* fd[1]只能用于数据写入。 */
    addfd(epollfd, pipefd[0]);

    // 设置信号处理函数
    addsig(SIGALRM);
    addsig(SIGTERM);
    bool stop_server = false;

    // 直接初始化FD_LIMIT个client_data对象，其数组索引是文件描述符
    client_data *users = new client_data[FD_LIMIT];
    bool timeout = false;
    // 定时
    alarm(TIMESLOT);

    while (!stop_server) {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1); /* 它在一段超时时间内等待一组文件描述符上的事件： */
        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; ++i) {
            int sockfd = events[i].data.fd;
            // 处理新到的客户连接
            if (sockfd == listenfd) {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);
                addfd(epollfd, connfd);
                users[connfd].address = client_address;
                users[connfd].sockfd = connfd;
                // 创建一个定时器，设置其回调函数和超时时间，然后绑定定时器和用户数据，并将定时器添加到timer_lst中
                util_timer *timer = new util_timer;
                timer->user_data = &users[connfd];
                timer->cb_func = cb_func;
                time_t cur = time(NULL);
                timer->expire = cur + 3 * TIMESLOT;
                users[connfd].timer = timer;
                timer_lst.add_timer(timer);
            // 处理信号
            } else if ((sockfd == pipefd[0]) && (events[i].events & EPOLLIN)) {
                int sig;
                char signals[1024];
                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if (ret == -1) {
                    // handle the error
                    continue;
                } else if (ret == 0) {
                    continue;
                } else {
                    for (int i = 0; i < ret; ++i) {
                        switch (signals[i]) {
                        case SIGALRM:
                            // 先标记为有定时任务，因为定时任务优先级比IO事件低，我们优先处理其他更重要的任务
                            timeout = true;
                            break;
                        
                        case SIGTERM:
                            stop_server = true;
                            break;
                        }
                    }
                }
            // 从客户连接上接收到数据
            } else if (events[i].events & EPOLLIN) {
                memset(users[sockfd].buf, '\0', BUFFER_SIZE);
                ret = recv(sockfd, users[sockfd].buf, BUFFER_SIZE - 1, 0);
                printf("get %d bytes of client data %s from %d\n", ret, users[sockfd].buf, sockfd);

                util_timer *timer = users[sockfd].timer;
                if (ret < 0) {
                    // 如果发生读错误，则关闭连接，并移除对应的定时器
                    if (errno != EAGAIN) {
                        cb_func(&users[sockfd]);
                        if (timer) {
                            timer_lst.del_timer(timer);
                        }
                    }
                } else if (ret == 0) {
                    // 如果对方关闭连接，则我们也关闭连接，并移除对应的定时器
                    cb_func(&users[sockfd]);
                    if (timer) {
                        timer_lst.del_timer(timer);
                    }
                } else {
                    // 如果客户连接上读到了数据，则调整该连接对应的定时器，以延迟该连接被关闭的时间
                    if (timer) {
                        time_t cur = time(NULL);
                        timer->expire = cur + 3 * TIMESLOT;
                        printf("adjust timer once\n");
                        timer_lst.adjust_timer(timer);
                    }
                }
            }
        }

        // 最后处理定时事件，因为IO事件的优先级更高，但这样会导致定时任务不能精确按预期的时间执行
        if (timeout) {
            timer_handler();
            timeout = false;
        }
    }

    close(listenfd);
    close(pipefd[1]);
    close(pipefd[0]);
    delete[] users;
    return 0;
}
