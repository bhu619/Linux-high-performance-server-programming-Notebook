#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* TCP客户端实现 */
int main() {

    // 1.创建套接字: AF_INET 表示使用 IPv4 地址，SOCK_STREAM 表示使用 TCP 连接。
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.连接服务器端: 设定服务器的 IP 地址和端口号（此处为 "192.168.177.146" 和 9999）。
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "10.1.1.161", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if(ret == -1) {
        perror("connect");
        exit(-1);
    }

    
    // 3.通信
    char recvBuf[1024] = {0};
    while(1) {

        char * data = "hello,i am client";
        // 通过 write 函数发送消息 "hello,i am client" 到服务器。
        write(fd, data , strlen(data));

        sleep(1);
        
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1) {
            perror("read");
            exit(-1);
        } else if(len > 0) {
            printf("recv server data : %s\n", recvBuf);
        } else if(len == 0) {
            // 如果 read 返回 0，表示服务器关闭了连接，客户端程序将结束循环并关闭连接。
            printf("server closed...");
            break;
        }

    }

    // 关闭连接
    close(fd);

    return 0;
}

