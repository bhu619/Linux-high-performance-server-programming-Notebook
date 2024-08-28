#include "TCPServerSocket.h"
#include <stdio.h>
#include <iostream>
#include <sys/select.h>
#include <stdlib.h>
#include <errno.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[]){

    if(argc <= 2){
        printf("Usage: %s ip_address port_number.\n", basename(argv[0]));
    }
    
    const char* ip = argv[1]; // ip地址
    int port = atoi(argv[2]); // 端口号

    TCPServerSocket server(ip, port);

    // 绑定socket到指定的地址和端口  
    if (server.bindSocket() < 0) {  
        throw std::runtime_error("Failed to bind socket");  
    }  

    // 开始监听连接，backlog参数指定了可以挂起（等待被accept）的连接数  
    if (server.listenSocket(5) < 0) {  
        throw std::runtime_error("Failed to listen on socket");  
    }  
    
    // 等待并接受一个客户端连接  
    struct sockaddr_in client_addr;  
    socklen_t client_addrlen = sizeof(client_addr);  
    int client_sockfd = server.acceptConnection(&client_addr, &client_addrlen);  

    if (client_sockfd < 0) {  
        throw std::runtime_error("Failed to accept connection");  
    }

    char buf[BUFF_SIZE];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds); /* 清除 fd_set 的所有位 */
    FD_ZERO(&exception_fds);

    while(1)
    {
        memset(buf, '\0', BUFF_SIZE);
        /* 每次调用select之前都要重新设置文件描述符，因为事件发生之后，文件描述符集合会被内核修改 */
        FD_SET(client_sockfd, &read_fds);
        FD_SET(client_sockfd, &exception_fds);

        int ret = select(client_sockfd + 1, &read_fds, NULL, &exception_fds, NULL);
        if(ret < 0) {
            printf("Selection failure.\n");
            break;
        }
        /* 处理可读事件，对于多个文件描述符，需要循环询问是否可读 */
        if (FD_ISSET(client_sockfd, &read_fds)) {
            ret = recv(client_sockfd, buf, BUFF_SIZE - 1, 0);
            if(ret <= 0) {
                if (ret == 0) { printf("Client disconnected.\n"); }
                else { printf("Receive error.\n"); }   
                break;
            }
            printf("Read: get %d bytes of normal data: %s\n", ret, buf);
        } 
        /* 处理异常事件, 采用带MSG_OOB标志的recv函数读取带外数据 */
        else if (FD_ISSET(client_sockfd, &exception_fds)){ 
            ret = recv(client_sockfd, buf, BUFF_SIZE - 1, MSG_OOB);
            if(ret <= 0) {
                if (ret == 0) { printf("Client disconnected.\n"); }
                else { printf("Receive error.\n"); }   
                break;
            }
            printf("Exception: get %d bytes of oob data: %s\n", ret, buf);
        }
    }
    close(client_sockfd);
    return 0;
}