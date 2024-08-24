#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <assert.h>  
#include <string.h>  
#include <unistd.h>  
#include <stdexcept> // 用于抛出异常  
  
class TCPClientSocket {  
private:  
    int sockfd;  
    struct sockaddr_in server_addr;  
  
public:  
    TCPClientSocket(const char* server_ip, int server_port) {  
        sockfd = socket(PF_INET, SOCK_STREAM, 0);  
        if (sockfd < 0) {  
            throw std::runtime_error("Failed to create socket");  
        }  
  
        memset(&server_addr, 0, sizeof(server_addr));  
        server_addr.sin_family = AF_INET;  
        server_addr.sin_port = htons(server_port);  
        if (inet_aton(server_ip, &server_addr.sin_addr) == 0) {  
            throw std::runtime_error("Invalid server IP address");  
        }  
    }  
  
    ~TCPClientSocket() {  
        close(sockfd);  
    }  
  
    // 连接到服务器  
    void connectToServer() {  
        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {  
            throw std::runtime_error("Failed to connect to server");  
        }  
    }  
  
    // 发送数据（示例方法，需要具体实现）  
    // void sendData(const char* data, size_t length);  
  
    // 接收数据（示例方法，需要具体实现）  
    // ssize_t receiveData(char* buffer, size_t buffer_size);  
  
    // 获取socket文件描述符
    int getSocketFd() const {  
        return sockfd;  
    }  
};  