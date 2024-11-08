## 概述
项目准备过程中，主要阅读了 **《Linux 高性能服务器编程》 游双** 一书。源码参考的是：[TinyWebServer](https://github.com/qinguoyi/TinyWebServer)，我在此源码的基础上做了一定的 **优化和修改**。

**我的代码：**[Github: myWebserver: 我的C++服务器项目](https://github.com/bhu619/myWebserver)

**我的 Webserver 项目总结：**[WebServer 项目解读 / 代码分析 / 改进](https://www.yuque.com/u39624144/zvaea9/aqktb26g923rsiv5)

**我的《Linux 高性能服务器编程》学习笔记：**[《Linux 高性能服务器编程》总结_红茶川的博客-CSDN博客](https://blog.csdn.net/teriri_/category_12760091.html?spm=1001.2014.3001.5482)

**我的 CSDN 博客：**[红茶川-CSDN博客](https://blog.csdn.net/Teriri_?spm=1000.2115.3001.5343)，上面同步更新了所有内容。

## 《Linux 高性能服务器编程》学习笔记
### 书本中的样例代码
书中的部分样例代码，我都在笔记中给出了可以运行的代码，大家可以编译运行一下看看效果。

所有代码我都放在了 Github 仓库：[《Linux 高性能服务器编程》—游双，阅读笔记及相关代码](https://github.com/bhu619/Linux-high-performance-server-programming-Notebook)

完整笔记：[《Linux 高性能服务器编程》总结_红茶川的博客-CSDN博客](https://blog.csdn.net/teriri_/category_12760091.html?spm=1001.2014.3001.5482)

---

[实战 1：TCP通信实现（服务器端和客户端）](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h#p2OYs)

[实战 2：使用 MSG_OOB 选项发送带外数据](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h#rvyoz)

[实战 3：实现一个简单的 CGI 服务器](https://www.yuque.com/u39624144/zvaea9/coklc3naf35zmiqs#uhNNJ)

[实战 4：测试 UID 和 EUID 的区别](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757#euBnM)

[实战 5：使用 setsid() 创建一个新的会话和进程组](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757#a1Hsx)

[实战 6：select 调用同时接收普通数据和带外数据](https://www.yuque.com/u39624144/zvaea9/ypvqw1ip7m8g06iw#Higr8)

[实战 7：使用 SIGURG 信号检测带外数据是否到达](https://www.yuque.com/u39624144/zvaea9/lmeph1l89eka5260#iDHr9)

[实战 8：使用 SO_SNDTIMEO 选项设置定时](https://www.yuque.com/u39624144/zvaea9/yp17h7vn7pyqeg8u#yGpN7)

[实战 9：利用 alarm 函数周期性触发 SIGALRM 信号](https://www.yuque.com/u39624144/zvaea9/yp17h7vn7pyqeg8u#mQQlT)

[实战 10：利用 Libevent 库实现一个“Hello World”程序](https://www.yuque.com/u39624144/zvaea9/bn1zz8726fc80b0g#mo5Ik)

[实战 11：在进程间传递文件描述符](https://www.yuque.com/u39624144/zvaea9/uqu0tqep71gn5x5n#t0560)

[实战 12：死锁举例](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#zI94q)

[实战 13：使用条件变量模拟实现生产者—消费者问题](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#h3K6i)

[实战 14：多线程环境中，使用fork调用产生的死锁问题](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#AR15e)

[实战 15：在一个线程中统一处理所有信号](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#HA174)

[实战 16：用进程池实现简单的 CGI 服务器](https://www.yuque.com/u39624144/zvaea9/qulr4t6shwwh9kmo#eKrIS)

### 第一篇 前置知识 TCP / IP 协议
[1. IP协议](https://www.yuque.com/u39624144/zvaea9/ufa1lv48std8gahd)

[2. TCP协议](https://www.yuque.com/u39624144/zvaea9/xbfffzg2tl63cqda)

[3. 访问一个网页的全过程](https://www.yuque.com/u39624144/zvaea9/kk0kn0i6bcd2iqq0)

### 第二篇 深入解析高性能服务器编程
[4. Linux网络编程基础API](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h)

[5. 高级 I/O 函数](https://www.yuque.com/u39624144/zvaea9/coklc3naf35zmiqs)

[6. Linux服务器程序规范](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757)

[7. 高性能服务器程序框架](https://www.yuque.com/u39624144/zvaea9/ocl1e8vzzdes4zgn)

[7. 高性能服务器程序框架](https://www.yuque.com/u39624144/zvaea9/ocl1e8vzzdes4zgn)

[8. I/O 复用](https://www.yuque.com/u39624144/zvaea9/ypvqw1ip7m8g06iw)

[9. 信号](https://www.yuque.com/u39624144/zvaea9/lmeph1l89eka5260)

[10. 定时器](https://www.yuque.com/u39624144/zvaea9/yp17h7vn7pyqeg8u)

[11. 高性能I/O框架库Libevent](https://www.yuque.com/u39624144/zvaea9/bn1zz8726fc80b0g)

[12. 多进程编程](https://www.yuque.com/u39624144/zvaea9/uqu0tqep71gn5x5n)

[14. 进程池和线程池](https://www.yuque.com/u39624144/zvaea9/qulr4t6shwwh9kmo)

[14. 进程池和线程池](https://www.yuque.com/u39624144/zvaea9/qulr4t6shwwh9kmo)

### 第三篇 高性能服务器优化与监测
[15. 服务器调制、调试和测试](https://www.yuque.com/u39624144/zvaea9/xozozt5a6b668adg)

## 其他参考
1. [什么是 web 服务器？ - 学习 Web 开发 | MDN](https://developer.mozilla.org/zh-CN/docs/Learn/Common_questions/Web_mechanics/What_is_a_web_server)
2. [基于 Linux 的 web 服务器_基于linux系统的webserve服务器开发-CSDN博客](https://blog.csdn.net/qq_42370809/article/details/126753879)
3. [代码随想录项目精讲系列-webserver.pdf](https://www.yuque.com/attachments/yuque/0/2024/pdf/40997209/1720596301277-75d1fb45-ecdf-4998-8c0c-e113aa6fba40.pdf)  密码：`dmsxlwb0624`
4. [Linux高性能服务器编程.pdf](https://www.yuque.com/attachments/yuque/0/2024/pdf/40997209/1724151873130-23d63211-4809-40ed-abb9-03a6b8441507.pdf)
5. [从零开始自制实现C++ High-Performance WebServer 全流程记录_c++ webserver项目 速成-CSDN博客](https://love6.blog.csdn.net/article/details/123754194)
6. [从零开始实现C++ TinyWebServer_JehanRio的博客-CSDN博客](https://blog.csdn.net/weixin_51322383/category_12307428.html)

