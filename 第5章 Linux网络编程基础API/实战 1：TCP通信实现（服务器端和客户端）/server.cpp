#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* TCP服务器端实现 */
int main() {

    /*
     * 1.创建socket(用于监听的套接字):
     *  使用 socket 函数创建一个套接字 listen_fd
     *  AF_INET: 表示使用 IPv4 协议
     *  SOCK_STREAM: 表示使用 TCP 连接。
     */  
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(listen_fd == -1) {
        perror("socket");
        exit(-1);
    }

    /*
     * 2.绑定/命名 socket: 
     *  struct sockaddr_in 用于指定服务器的地址和端口。
     *  INADDR_ANY 让服务器绑定到所有可用的网络接口（即可以接受任何 IP 地址的连接）。
     *  使用 bind 函数将套接字与指定的 IP 地址和端口绑定。
     *  如果 bind 返回 -1，表示绑定失败，输出错误信息并退出程序。
     */
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    // inet_pton(AF_INET, "192.168.193.128", &saddr.sin_addr.s_addr);
    saddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    saddr.sin_port = htons(8080);
    int ret = bind(listen_fd, (struct sockaddr *)&saddr, sizeof(saddr));

    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    /*
     * 3.监听连接
     *  listen 函数使套接字进入监听状态，准备接收来自客户端的连接请求。
     *  第二个参数 8 指定了连接队列的最大长度，即最多可以有 8 个连接请求排队等待处理。
     *  如果 listen 返回 -1，表示监听失败，输出错误信息并退出程序。
     */ 
    ret = listen(listen_fd, 8);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    /*
     * 4.接收客户端连接
     *  使用 accept 函数接收客户端的连接请求，accept 返回一个新的套接字 cfd，用于与客户端通信。
     *  clientaddr 用于存储客户端的地址信息。
     *  如果 accept 返回 -1，表示接收连接失败，输出错误信息并退出程序。
    */
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int cfd = accept(listen_fd, (struct sockaddr *)&clientaddr, &len);
    
    if(cfd == -1) {
        perror("accept");
        exit(-1);
    }

    /*
     * 5. 输出客户端的信息
     *  inet_ntop 函数将客户端的 IP 地址从网络字节序转换为点分十进制字符串格式，并输出。
     *  ntohs 函数将客户端的端口号从网络字节序转换为主机字节序，并输出。
     */
    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client ip is %s, port is %d\n", clientIP, clientPort);

    // 6.通信
    char recvBuf[1024] = {0};
    while(1) {
        
        // 获取客户端的数据
        int num = read(cfd, recvBuf, sizeof(recvBuf));
        if(num == -1) {
            perror("read");
            exit(-1);
        } else if(num > 0) {
            printf("recv client data : %s\n", recvBuf);
        } else if(num == 0) {
            // 表示客户端断开连接
            printf("clinet closed...");
            break;
        }

        char * data = "hello,i am server";
        // 给客户端发送数据
        write(cfd, data, strlen(data));
    }
   
    // 7. 关闭文件描述符
    close(cfd);
    close(listen_fd);

    return 0;
}
