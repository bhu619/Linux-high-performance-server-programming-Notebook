#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>

/* 超时连接函数 
 * 这个函数的作用是尝试与指定IP地址和端口的服务器建立连接，
 * 并设置一个连接超时时间。
 */
int timeout_connect(const char *ip, int port, int time) {
    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    
    // SO_RCVTIMEO和SO_SNDTIMEO套接字选项对应的值类型为timeval，这和select函数的超时参数类型相同
    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;
    socklen_t len = sizeof(timeout);
    ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
    assert(ret != -1);

    /*
     * 如果连接在指定时间内没有成功建立，connect() 函数将返回 -1，
     * 并且 errno 会被设置为 EINPROGRESS，表示连接超时。
     */
    printf("Attempting to connect...\n");
    ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    printf("Connect returned: %d\n", ret);

    if (ret == -1) {
        // 超时对应的错误号是EINPROGRESS，此时就可执行定时任务了
        if (errno == EINPROGRESS) {
            printf("conencting timeout, process timeout logic\n");
            return -1;
        }
        printf("error occur when connecting to server\n");
        return -1;
    }

    return sockfd;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = timeout_connect(ip, port, 1);
    if (sockfd < 0) {
        return 1;
    }
    return 0;
}