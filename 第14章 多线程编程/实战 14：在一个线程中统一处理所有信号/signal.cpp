#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

// perror函数根据全局errno值打印其相应的错误信息到标准错误
#define handle_error_en(en, msg) \ 
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

/* 在 sig_thread 函数中，线程循环调用 sigwait 来等待信号 */
static void *sig_thread(void *arg) {
    sigset_t *set = (sigset_t *)arg;
    int s, sig;

    for (; ; ) {
        // 第二步，调用sigwait等待信号
        s = sigwait(set, &sig);
        if (s != 0) {
            handle_error_en(s, "sigwait");
        }
        printf("Signal handling thread got signal %d\n", sig);
    }
}

int main(int argc, char *argv[]) {
    printf("The PID of this process is: %d\n", getpid()); /* 获取进程 PID */
    
    pthread_t thread;			/* 线程 */
    sigset_t set;				/* 信号集 */
    int s;

    /* 第一步，在主线程中设置信号掩码，信号集set被初始化并添加了SIGQUIT和SIGUSR1信号： */
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGUSR1);

    /* 使用 pthread_sigmask 来阻塞这些信号 */
    s = pthread_sigmask(SIG_BLOCK, &set, NULL);
    if (s != 0) {
        handle_error_en(s, "pthread_sigmask");
    }

    /* 创建处理信号的线程 */
    s = pthread_create(&thread, NULL, &sig_thread, (void *)&set);
    if (s != 0) {
        handle_error_en(s, "thread_create");
    }

    pause();
}