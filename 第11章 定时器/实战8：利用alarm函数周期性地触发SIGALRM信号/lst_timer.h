#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 64

// 前向声明，我们需要在client_data结构中定义该结构的指针类型
class util_timer;

// 用户数据结构
struct client_data {
    sockaddr_in address;    /* 客户socket地址 */
    int sockfd;             /* socket文件描述符 */
    char buf[BUFFER_SIZE];  /* 读缓冲区 */
    util_timer *timer;      /* 定时器 */
};

// 定时器类
class util_timer {
public:
    util_timer() : prev(NULL), next(NULL) {}

    // 任务执行时间，UNIX时间戳
    time_t expire;
    // 任务回调函数
    void (*cb_func)(client_data *);
    // 回调函数处理的客户数据，由定时器的执行者传给回调函数
    client_data *user_data;
    // 指向前一个定时器
    util_timer *prev;
    // 指向后一个定时器
    util_timer *next;
};

// 定时器链表，它是一个升序、双向链表，且有头节点和尾节点
class sort_timer_lst {
public:
    sort_timer_lst() : head(NULL), tail(NULL) {}
    // 链表被删除时，删除其中所有定时器
    ~sort_timer_lst() {
        util_timer *tmp = head;
        while (tmp) {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }

    // 将目标定时器timer参数添加到链表中
    void add_timer(util_timer *timer) {
        if (!timer) {
            return;
        }
        if (!head) {
            head = tail = timer;
            return;
        }
        
        // 如果timer中的执行时间小于链表中所有定时器的超时时间，则将其放在链表头部
        if (timer->expire < head->expire) {
            timer->next = head;
            head->prev = timer;
            head = timer;
            return;
        }
        // 否则调用重载函数add_timer(util_timer, util_timer)将其放到链表中合适的位置，以保证链表的升序特性
        add_timer(timer, head);
    }

    // 调整定时任务的执行时间，本函数只处理执行时间延后的情况，即将该定时器向链表尾部移动
    void adjust_timer(util_timer *timer) {
        if (!timer) {
            return;
        }
        util_timer *tmp = timer->next;
        // 如果被调整的目标定时器在链表尾，或该定时器的超时值仍小于下一个定时器的超时值，则不用调整
        if (!tmp || (timer->expire < tmp->expire)) {
            return;
        }
        // 如果目标定时器在链表头，则将该定时器从链表中取出并重新插入链表
        if (timer == head) {
            head = head->next;
            head->prev = NULL;
            timer->next = NULL;
            add_timer(timer, head);
        // 如果目标定时器不是链表头节点，则将该定时器从链表中取出，然后插入其原来所在位置之后的链表中
        } else {
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            add_timer(timer, timer->next);
        }
    }

    // 将目标定时器timer从链表中删除
    void del_timer(util_timer *timer) {
        if (!timer) {
            return;
        }
        // 当链表中只有要删除的那个定时器时
        if ((timer == head) && (timer == tail)) {
            delete timer;
            head = NULL;
            tail = NULL;
            return;
        }
        // 如果链表中至少有两个定时器，且目标定时器时链表头节点，则将链表的头节点重置为原头节点的下一个节点
        if (timer == head) {
            head = head->next;
            head->prev = NULL;
            delete timer;
            return;
        }
        // 如果链表中至少有两个定时器，且目标定时器时链表尾节点，则将链表的尾节点重置为原尾节点的前一个节点
        if (timer == tail) {
            tail = tail->prev;
            tail->next = NULL;
            delete timer;
            return;
        }
        // 如果，目标定时器位于链表中间，则把它前后的定时器串联起来，然后删除目标定时器
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
    }

    // SIGALRM信号每次触发就在其信号处理函数（如果使用统一事件源，则是主函数）中执行一次tick函数，处理链表上的到期任务
    void tick() {
        if (!head) {
            return;
        }
        printf("timer tick\n");
        // 获得系统当前UNIX时间戳
        time_t cur = time(NULL);
        util_timer *tmp = head;

        // 从头节点开始依次处理每个定时器，直到遇到一个尚未到期的定时器
        while (tmp) {
            // 每个定时器都使用绝对时间作为超时值，因此我们可把定时器的超时值和系统当前时间作比较
            if (cur < tmp->expire) {
                break;
            }
            // 调用定时器的回调函数，以执行定时任务
            tmp->cb_func(tmp->user_data);
            // 执行完定时器中的任务后，将其从链表中删除，并重置链表头节点
            head = tmp->next;
            if (head) {
                head->prev = NULL;
            }
            delete tmp;
            tmp = head;
        }
    }

private:
    // 一个重载的辅助函数，它被公有的add_timer和adjust_timer函数调用
    // 该函数将目标定时器timer参数添加到节点lst_head参数后的链表中
    void add_timer(util_timer *timer, util_timer *lst_head) {
        util_timer *prev = lst_head;
        util_timer *tmp = prev->next;
        // 遍历lst_head节点后的部分链表，直到找到一个超时时间大于目标定时器超时时间的节点，并将目标定时器插入该节点前
        while (tmp) {
            if (timer->expire < tmp->expire) {
                prev->next = timer;
                timer->next = tmp;
                tmp->prev = timer;
                timer->prev = prev;
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }

        // 如果遍历完lst_head节点后的链表，仍未找到超时时间大于目标定时器的超时时间的节点，则将目标定时器作为链表尾
        if (!tmp) {
            prev->next = timer;
            timer->prev = prev;
            timer->next = NULL;
            tail = timer;
        }
    }

    util_timer *head;
    util_timer *tail;
};
#endif
