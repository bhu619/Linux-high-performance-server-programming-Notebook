# webserver
Linux高性能服务器编程，笔记及相关代码

<a name="gMeAF"></a>
# 项目总结
主要阅读了**《Linux 高性能服务器编程》游双 **一书。
<a name="yaVRA"></a>
## 第一篇 前置知识 TCP / IP 协议
[1. C++ TinyWebServer项目总结（1. 配置安装）](https://www.yuque.com/u39624144/zvaea9/cbr8n7reuf3rgw58?view=doc_embed)<br />[2. C++ TinyWebServer项目总结（2. IP协议）](https://www.yuque.com/u39624144/zvaea9/ufa1lv48std8gahd?view=doc_embed)<br />[3. C++ TinyWebServer项目总结（3. TCP协议）](https://www.yuque.com/u39624144/zvaea9/xbfffzg2tl63cqda?view=doc_embed)<br />[4. C++ TinyWebServer项目总结（4. 访问一个网页的全过程）](https://www.yuque.com/u39624144/zvaea9/kk0kn0i6bcd2iqq0?view=doc_embed)
<a name="vJU1d"></a>
## 第二篇 深入解析高性能服务器编程
[5. C++ TinyWebServer项目总结（5. Linux网络编程基础API）](https://www.yuque.com/u39624144/zvaea9/xsil4chqwb5qqc0h?view=doc_embed)<br />[6. C++ TinyWebServer项目总结（6. 高级 I/O 函数）](https://www.yuque.com/u39624144/zvaea9/coklc3naf35zmiqs?view=doc_embed)<br />[7. C++ TinyWebServer项目总结（7. Linux服务器程序规范）](https://www.yuque.com/u39624144/zvaea9/uykylirmss5wl757?view=doc_embed)<br />[8. C++ TinyWebServer项目总结（8. 高性能服务器程序框架）](https://www.yuque.com/u39624144/zvaea9/ocl1e8vzzdes4zgn?view=doc_embed)<br />[9. C++ TinyWebServer项目总结（9. I/O 复用）](https://www.yuque.com/u39624144/zvaea9/ypvqw1ip7m8g06iw?view=doc_embed)<br />[10. C++ TinyWebServer项目总结（10. 信号）](https://www.yuque.com/u39624144/zvaea9/lmeph1l89eka5260?view=doc_embed)
<a name="YX7xk"></a>
## 第三篇 高性能服务器优化与监测
<a name="uIePR"></a>
# TinyWebServer
GitHub地址：[https://github.com/qinguoyi/TinyWebServer](https://github.com/qinguoyi/TinyWebServer)

- [小白视角：一文读懂社长的TinyWebServer](https://huixxi.github.io/2020/06/02/%E5%B0%8F%E7%99%BD%E8%A7%86%E8%A7%92%EF%BC%9A%E4%B8%80%E6%96%87%E8%AF%BB%E6%87%82%E7%A4%BE%E9%95%BF%E7%9A%84TinyWebServer/#more)
- [最新版Web服务器项目详解 - 01 线程同步机制封装类](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=3&sn=5840ff698e3f963c7855d702e842ec47&chksm=83ffbefeb48837e86fed9754986bca6db364a6fe2e2923549a378e8e5dec6e3cf732cdb198e2&scene=0&xtrack=1#rd)
- [最新版Web服务器项目详解 - 02 半同步半反应堆线程池（上）](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=4&sn=caa323faf0c51d882453c0e0c6a62282&chksm=83ffbefeb48837e841a6dbff292217475d9075e91cbe14042ad6e55b87437dcd01e6d9219e7d&scene=0&xtrack=1#rd)
- [最新版Web服务器项目详解 - 03 半同步半反应堆线程池（下）](https://mp.weixin.qq.com/s/PB8vMwi8sB4Jw3WzAKpWOQ)
- [最新版Web服务器项目详解 - 04 http连接处理（上）](https://mp.weixin.qq.com/s/BfnNl-3jc_x5WPrWEJGdzQ)
- [最新版Web服务器项目详解 - 05 http连接处理（中）](https://mp.weixin.qq.com/s/wAQHU-QZiRt1VACMZZjNlw)
- [最新版Web服务器项目详解 - 06 http连接处理（下）](https://mp.weixin.qq.com/s/451xNaSFHxcxfKlPBV3OCg)
- [最新版Web服务器项目详解 - 07 定时器处理非活动连接（上）](https://mp.weixin.qq.com/s/mmXLqh_NywhBXJvI45hchA)
- [最新版Web服务器项目详解 - 08 定时器处理非活动连接（下）](https://mp.weixin.qq.com/s/fb_OUnlV1SGuOUdrGrzVgg)
- [最新版Web服务器项目详解 - 09 日志系统（上）](https://mp.weixin.qq.com/s/IWAlPzVDkR2ZRI5iirEfCg)
- [最新版Web服务器项目详解 - 10 日志系统（下）](https://mp.weixin.qq.com/s/f-ujwFyCe1LZa3EB561ehA)
- [最新版Web服务器项目详解 - 11 数据库连接池](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274326&idx=1&sn=5af78e2bf6552c46ae9ab2aa22faf839&chksm=83ffbe8eb4883798c3abb82ddd124c8100a39ef41ab8d04abe42d344067d5e1ac1b0cac9d9a3&token=1450918099&lang=zh_CN#rd)
- [最新版Web服务器项目详解 - 12 注册登录](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274431&idx=4&sn=7595a70f06a79cb7abaebcd939e0cbee&chksm=83ffb167b4883871ce110aeb23e04acf835ef41016517247263a2c3ab6f8e615607858127ea6&token=1686112912&lang=zh_CN#rd)
- [最新版Web服务器项目详解 - 13 踩坑与面试题](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274431&idx=1&sn=2dd28c92f5d9704a57c001a3d2630b69&chksm=83ffb167b48838715810b27b8f8b9a576023ee5c08a8e5d91df5baf396732de51268d1bf2a4e&token=1686112912&lang=zh_CN#rd)
<a name="WC5O4"></a>
# 代码随想录PDF文档
[代码随想录项目精讲系列-webserver.pdf](https://www.yuque.com/attachments/yuque/0/2024/pdf/40997209/1720596301277-75d1fb45-ecdf-4998-8c0c-e113aa6fba40.pdf?_lake_card=%7B%22src%22%3A%22https%3A%2F%2Fwww.yuque.com%2Fattachments%2Fyuque%2F0%2F2024%2Fpdf%2F40997209%2F1720596301277-75d1fb45-ecdf-4998-8c0c-e113aa6fba40.pdf%22%2C%22name%22%3A%22%E4%BB%A3%E7%A0%81%E9%9A%8F%E6%83%B3%E5%BD%95%E9%A1%B9%E7%9B%AE%E7%B2%BE%E8%AE%B2%E7%B3%BB%E5%88%97-webserver.pdf%22%2C%22size%22%3A4161803%2C%22ext%22%3A%22pdf%22%2C%22source%22%3A%22%22%2C%22status%22%3A%22done%22%2C%22download%22%3Atrue%2C%22taskId%22%3A%22ua0643a9e-af55-4bff-b5b1-e545ebf9895%22%2C%22taskType%22%3A%22upload%22%2C%22type%22%3A%22application%2Fpdf%22%2C%22__spacing%22%3A%22both%22%2C%22mode%22%3A%22title%22%2C%22id%22%3A%22ud2fef034%22%2C%22margin%22%3A%7B%22top%22%3Atrue%2C%22bottom%22%3Atrue%7D%2C%22card%22%3A%22file%22%7D)<br />密码：dmsxlwb0624
<a name="Xdo0U"></a>
# Linux 高性能服务器编程
[Linux高性能服务器编程.pdf](https://www.yuque.com/attachments/yuque/0/2024/pdf/40997209/1724151873130-23d63211-4809-40ed-abb9-03a6b8441507.pdf?_lake_card=%7B%22src%22%3A%22https%3A%2F%2Fwww.yuque.com%2Fattachments%2Fyuque%2F0%2F2024%2Fpdf%2F40997209%2F1724151873130-23d63211-4809-40ed-abb9-03a6b8441507.pdf%22%2C%22name%22%3A%22Linux%E9%AB%98%E6%80%A7%E8%83%BD%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%BC%96%E7%A8%8B.pdf%22%2C%22size%22%3A34037912%2C%22ext%22%3A%22pdf%22%2C%22source%22%3A%22%22%2C%22status%22%3A%22done%22%2C%22download%22%3Atrue%2C%22taskId%22%3A%22ub10bcc41-fb43-47a3-b806-ba5054bc449%22%2C%22taskType%22%3A%22upload%22%2C%22type%22%3A%22application%2Fpdf%22%2C%22__spacing%22%3A%22both%22%2C%22mode%22%3A%22title%22%2C%22id%22%3A%22uef4188be%22%2C%22margin%22%3A%7B%22top%22%3Atrue%2C%22bottom%22%3Atrue%7D%2C%22card%22%3A%22file%22%7D)
<a name="zHtjU"></a>
# 其他参考
[什么是 web 服务器？ - 学习 Web 开发 | MDN](https://developer.mozilla.org/zh-CN/docs/Learn/Common_questions/Web_mechanics/What_is_a_web_server)
