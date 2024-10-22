# 《Linux 高性能服务器编程》
[Linux高性能服务器编程.pdf](https://www.yuque.com/attachments/yuque/0/2024/pdf/40997209/1724151873130-23d63211-4809-40ed-abb9-03a6b8441507.pdf?_lake_card=%7B%22src%22%3A%22https%3A%2F%2Fwww.yuque.com%2Fattachments%2Fyuque%2F0%2F2024%2Fpdf%2F40997209%2F1724151873130-23d63211-4809-40ed-abb9-03a6b8441507.pdf%22%2C%22name%22%3A%22Linux%E9%AB%98%E6%80%A7%E8%83%BD%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%BC%96%E7%A8%8B.pdf%22%2C%22size%22%3A34037912%2C%22ext%22%3A%22pdf%22%2C%22source%22%3A%22%22%2C%22status%22%3A%22done%22%2C%22download%22%3Atrue%2C%22taskId%22%3A%22ub10bcc41-fb43-47a3-b806-ba5054bc449%22%2C%22taskType%22%3A%22upload%22%2C%22type%22%3A%22application%2Fpdf%22%2C%22__spacing%22%3A%22both%22%2C%22mode%22%3A%22title%22%2C%22id%22%3A%22uef4188be%22%2C%22margin%22%3A%7B%22top%22%3Atrue%2C%22bottom%22%3Atrue%7D%2C%22card%22%3A%22file%22%7D)

# 阅读笔记
## 书本中的样例代码
[实战 1：TCP通信实现（服务器端和客户端）](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h#p2OYs)<br />
[实战 2：使用 MSG_OOB 选项发送带外数据](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h#rvyoz)<br />
[实战 3：实现一个简单的 CGI 服务器](https://www.yuque.com/u39624144/zvaea9/coklc3naf35zmiqs#uhNNJ)<br />
[实战 4：测试 UID 和 EUID 的区别](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757#euBnM)<br />
[实战 5：使用 setsid() 创建一个新的会话和进程组](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757#a1Hsx)<br />
[实战 6：select 调用同时接收普通数据和带外数据](https://www.yuque.com/u39624144/zvaea9/ypvqw1ip7m8g06iw#Higr8)<br />
[实战 7：使用 SIGURG 信号检测带外数据是否到达](https://www.yuque.com/u39624144/zvaea9/lmeph1l89eka5260#iDHr9)<br />
[实战 8：使用 SO_SNDTIMEO 选项设置定时](https://www.yuque.com/u39624144/zvaea9/yp17h7vn7pyqeg8u#yGpN7)<br />
[实战 9：利用 alarm 函数周期性触发 SIGALRM 信号](https://www.yuque.com/u39624144/zvaea9/yp17h7vn7pyqeg8u#mQQlT)<br />
[实战 10：利用 Libevent 库实现一个“Hello World”程序](https://www.yuque.com/u39624144/zvaea9/bn1zz8726fc80b0g#mo5Ik)<br />
[实战 11：在进程间传递文件描述符](https://www.yuque.com/u39624144/zvaea9/uqu0tqep71gn5x5n#t0560)<br />
[实战 12：死锁举例](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#zI94q)<br />
[实战 13：使用条件变量模拟实现生产者—消费者问题](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#h3K6i)<br />
[实战 14：多线程环境中，使用fork调用产生的死锁问题](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#AR15e)<br />
[实战 15：在一个线程中统一处理所有信号](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc#HA174)<br />
[实战 16：用进程池实现简单的 CGI 服务器](https://www.yuque.com/u39624144/zvaea9/qulr4t6shwwh9kmo#eKrIS)

## 第一篇 前置知识 TCP / IP 协议
[1. C++ TinyWebServer项目总结（1. 配置安装）](https://www.yuque.com/u39624144/zvaea9/cbr8n7reuf3rgw58?view=doc_embed)<br />
[2. C++ TinyWebServer项目总结（2. IP协议）](https://www.yuque.com/u39624144/zvaea9/ufa1lv48std8gahd?view=doc_embed)<br />
[3. C++ TinyWebServer项目总结（3. TCP协议）](https://www.yuque.com/u39624144/zvaea9/xbfffzg2tl63cqda?view=doc_embed)<br />
[4. C++ TinyWebServer项目总结（4. 访问一个网页的全过程）](https://www.yuque.com/u39624144/zvaea9/kk0kn0i6bcd2iqq0?view=doc_embed)

## 第二篇 深入解析高性能服务器编程
[5. C++ TinyWebServer项目总结（5. Linux网络编程基础API）](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h?view=doc_embed)<br />
[6. C++ TinyWebServer项目总结（6. 高级 I/O 函数）](https://www.yuque.com/u39624144/zvaea9/coklc3naf35zmiqs?view=doc_embed)<br />
[7. C++ TinyWebServer项目总结（7. Linux服务器程序规范）](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757?view=doc_embed)<br />
[8. C++ TinyWebServer项目总结（8. 高性能服务器程序框架）](https://www.yuque.com/u39624144/zvaea9/ocl1e8vzzdes4zgn?view=doc_embed)<br />
[9. C++ TinyWebServer项目总结（9. I/O 复用）](https://www.yuque.com/u39624144/zvaea9/ypvqw1ip7m8g06iw?view=doc_embed)<br />
[10. C++ TinyWebServer项目总结（10. 信号）](https://www.yuque.com/u39624144/zvaea9/lmeph1l89eka5260?view=doc_embed)<br />
[11. C++ TinyWebServer项目总结（11. 定时器）](https://www.yuque.com/u39624144/zvaea9/yp17h7vn7pyqeg8u?view=doc_embed)<br />
[12. C++ TinyWebServer项目总结（12. 高性能I/O框架库Libevent）](https://www.yuque.com/u39624144/zvaea9/bn1zz8726fc80b0g?view=doc_embed)<br />
[13. C++ TinyWebServer项目总结（13. 多进程编程）](https://www.yuque.com/u39624144/zvaea9/uqu0tqep71gn5x5n?view=doc_embed)<br />
[14. C++ TinyWebServer项目总结（14. 多线程编程）](https://www.yuque.com/u39624144/zvaea9/gc463q2ptu28gzpc?view=doc_embed)<br />
[15. C++ TinyWebServer项目总结（15. 进程池和线程池）](https://www.yuque.com/u39624144/zvaea9/qulr4t6shwwh9kmo)

## 第三篇 高性能服务器优化与监测
[16. C++ TinyWebServer项目总结（16. 服务器调制、调试和测试）](https://www.yuque.com/u39624144/zvaea9/xozozt5a6b668adg)

# 其他参考
[什么是 web 服务器？ - 学习 Web 开发 | MDN](https://developer.mozilla.org/zh-CN/docs/Learn/Common_questions/Web_mechanics/What_is_a_web_server)<br />[基于 Linux 的 web 服务器_基于linux系统的webserve服务器开发-CSDN博客](https://blog.csdn.net/qq_42370809/article/details/126753879)
