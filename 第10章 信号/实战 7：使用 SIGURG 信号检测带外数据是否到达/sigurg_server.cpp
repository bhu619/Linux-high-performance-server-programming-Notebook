#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <libgen.h>

#define BUF_SIZE 1024

static int connfd;

// SIGURG信号的处理函数
void sig_urg(int sig) {
    int save_errno = errno;
    char buffer[BUF_SIZE];
    memset(buffer, '\0', BUF_SIZE);
    
    int ret;
    while ((ret = recv(connfd, buffer, BUF_SIZE - 1, MSG_OOB)) < 0) {
        if (errno == EWOULDBLOCK) {
            continue; // 如果接收缓冲区满了,继续读取,直到接收到带外数据
        } else {
            break; // 处理其他错误情况
        }
    }
    if (ret > 0) {
        printf("got %d bytes of oob data '%s'\n", ret, buffer);
    }
    
    errno = save_errno;
}

void addsig(int sig, void (*sig_handler)(int)) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (connfd < 0) {
        printf("errno is: %d\n", errno);
    } else {
        addsig(SIGURG, sig_urg);
        // 我们必须设置socket的宿主进程或进程组
        fcntl(connfd, F_SETOWN, getpid());

        char buffer[BUF_SIZE];
        // 循环接收普通数据
        while (1) {
            memset(buffer, '\0', BUF_SIZE);
            ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
            if (ret < 0) {
                if(errno == EINTR) {
                    continue; // 如果recv因信号中断,则继续读取
                }
                break; // 处理其他错误
            } else if (ret == 0) {
                printf("Client disconnected.\n");
                break;
            }
            printf("get %d bytes of normal data '%s'\n", ret, buffer);
        }
        close(connfd);
    }
    close(sock);
    return 0;
}