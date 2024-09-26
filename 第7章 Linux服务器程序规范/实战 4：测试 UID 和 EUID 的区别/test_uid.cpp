#include <unistd.h> // <unistd.h>（Unix Standard Definitions）头文件提供对POSIX操作系统API的访问，主要用于提供对POSIX操作系统API的函数原型、符号常量等。
#include <stdio.h>  // <stdio.h>（Standard Input Output Header）头文件提供了进行输入和输出操作的函数。

int main(){
    uid_t uid = getuid();
    uid_t euid = geteuid();
    
    printf("userid :%d , euid: %d \n", uid, euid);
    return 0;
}