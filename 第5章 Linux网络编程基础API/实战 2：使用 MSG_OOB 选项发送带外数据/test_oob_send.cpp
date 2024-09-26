#include "TCPClientSocket.h"
#include <iostream>
#include <stdlib.h>

// 客户端发送TCP报文
int main(int argc, char *argv[]){
    if (argc <= 2){
        std::cout << "usage: " << basename(argv[0]) << " ip_address port_number" << std::endl;
        return 1;
    }

    const char* ip = argv[1]; // ip地址
    int port = atoi(argv[2]); // 端口号

    TCPClientSocket client(ip, port);

    client.connectToServer(); // 连接到服务器端

    const char* oob_data = "abc";
    const char* normal_data = "123";

    int sockfd = client.getSocketFd(); // 获取文件描述符

    send(sockfd, normal_data, strlen(normal_data), 0);
    sleep(1); // 加入延时,确保带外数据发送
    send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
    sleep(1); // 再次加入延时,确保服务器有时间处理带外数据
    send(sockfd, normal_data, strlen(normal_data), 0);
    
    return 0;
}
