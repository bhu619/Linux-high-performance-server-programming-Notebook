#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // 创建一个子进程
    pid = fork();
    printf("Child Process ID: %d\n", pid);

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // 父进程退出，使子进程成为孤儿进程
        exit(EXIT_SUCCESS);
    }

    // 子进程开始执行，创建新的会话
    pid_t sid = setsid();
    if (sid < 0) {
        perror("setsid failed");
        exit(EXIT_FAILURE);
    }

    // 此时，进程已经成为新的会话和进程组的首领
    printf("New session ID: %d\n", sid);

    // 继续执行其他代码...

    return 0;
}
