#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
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

    // 创建套接字
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // 绑定套接字
    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    // 监听套接字，最大等待连接队列的长度为5
    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);

    // 接受客户端连接
    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (connfd < 0) {
        printf("errno is: %d\n", errno);
    } else {
        // 先关闭标准输出文件描述符STDOUT_FILENO，其值为1
        close(STDOUT_FILENO);
        // 复制socket文件描述符connfd，由于dup函数总是返回系统中最小的可用文件描述符
        // 因此dup参数实际返回的是1，即之前关闭的标准输出文件描述符的值
        // 这样服务器输出到标准输出的内容会直接发送到与客户连接对应的socket上
        dup(connfd);
        printf("abcd\n");
        close(connfd);
    }

    close(sock);
    return 0;
}