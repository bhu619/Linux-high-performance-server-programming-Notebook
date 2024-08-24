#include "TCPServerSocket.h"
#include <iostream>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 1024

// 服务器接收TCP报文
int main(int argc, char *argv[]){
    if(argc <= 2){
        std::cout << "Usage: " << basename(argv[0]) << " ip_address port_number" << std::endl;
        return 1;
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

    // 可以使用client_sockfd来与客户端进行通信  

    char buffer[BUF_SIZE];
    memset(buffer, '\0', BUF_SIZE);
    int ret = recv(client_sockfd, buffer, BUF_SIZE - 1, 0);
    std::cout << "got " << ret << " bytes of normal data '" << buffer << "'" << std::endl;
    
    memset(buffer, '\0', BUF_SIZE);
    ret = recv(client_sockfd, buffer, BUF_SIZE - 1, MSG_OOB);
    std::cout << "got " << ret << " bytes of odd data '" << buffer << "'" << std::endl;
    
    memset(buffer, '\0', BUF_SIZE);
    ret = recv(client_sockfd, buffer, BUF_SIZE - 1, 0);
    std::cout << "got " << ret << " bytes of normal data '" << buffer << "'" << std::endl;

    close(client_sockfd);

    return 0;
}
