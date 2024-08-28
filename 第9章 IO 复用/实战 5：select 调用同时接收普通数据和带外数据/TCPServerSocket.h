#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

// 创建IPv4 服务器端 socket
class TCPServerSocket{

private:
    struct sockaddr_in address;
    int sockfd;

public:
    TCPServerSocket(const char *ip, int port){
        sockfd = socket( PF_INET, SOCK_STREAM, 0 );
        assert(sockfd >= 0);
        memset(&address, 0, sizeof(address)); 
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        assert(inet_aton(ip, &address.sin_addr) == 1);
    }
    ~TCPServerSocket() {  
        close(sockfd);  
    } 
    int bindSocket();
    int listenSocket(int backlog);
    int acceptConnection(struct sockaddr_in* client, socklen_t* client_addrlength);
    int getSocketFd() const { return sockfd; }  // 获取socket文件描述符
};

// 命名socket
int TCPServerSocket::bindSocket(){
    return bind(sockfd, (struct sockaddr*)&address, sizeof(address));
}

// 监听socket
int TCPServerSocket::listenSocket(int backlog){
    return listen(sockfd, backlog);
}

// 接受连接
int TCPServerSocket::acceptConnection(struct sockaddr_in* client, socklen_t* client_addrlength){
   // 注意：这里应该是传递client的指针的地址给accept  
    int newsockfd = accept(sockfd, (struct sockaddr*)client, client_addrlength);  
    if (newsockfd < 0) {  
        // 可以选择抛出异常或返回错误码  
        return -1; // 或者 throw std::runtime_error("Failed to accept connection");  
    }  
    return newsockfd; // 返回新的socket文件描述符  
}  

// 注意：在实际使用中，您可能还需要检查bind和listen的返回值以确保它们成功执行。  
// 此外，对于accept函数，通常我们会检查它的返回值以确认连接是否被成功接受。  
// 如果需要处理多个客户端连接，您可能需要将accept调用放在一个循环中，或者使用多线程/多进程来处理每个连接。
