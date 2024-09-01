# Tiny Web Server
Linux下基于**单Reactor多线程模型**的Web服务器. 

- 使用**epoll(ET模式) + 非阻塞socket**, 参考[muduo](https://github.com/chenshuo/muduo/blob/master/muduo/net/Channel.h)的Channel抽象出socket的事件, epoll触发事件后交给线程池处理. 
- 基于**Ragel状态机**的HTTP报文解析器, 支持**GET和POST请求**, 以及**200, 400, 403, 404等响应状态**. 状态机的头文件参考了大名鼎鼎的[http-parser](https://github.com/nodejs/http-parser), Ragel的介绍见[其主页](https://www.colm.net/open-source/ragel/). 
- 基于阻塞队列和双缓冲的**异步日志**系统. 参考[muduo](https://github.com/chenshuo/muduo/blob/master/muduo/base/AsyncLogging.h)和[minilog](https://github.com/archibate/minilog). 
- 简单的线程池实现, 只要往里面塞任务即可. 参考[CThreadPool](https://github.com/ChunelFeng/CThreadPool). 
- 基于红黑树(std::set)的定时器管理器. 参考[muduo](https://github.com/chenshuo/muduo/blob/master/muduo/net/TimerQueue.h). 



### TODO

- [ ] 使用epoll的ET模式时, 写操作存在一定问题, 试试直接用LT模式. 
- [ ] std::coroutine. 
- [ ] 线程池的自动扩缩容, 负载均衡. 



### References

 - [muduo](https://github.com/chenshuo/muduo)
 - [TinyWebServer](https://github.com/qinguoyi/TinyWebServer)
 - [WebServer](https://github.com/linyacool/WebServer)
 - [trantor](https://github.com/an-tao/trantor)
 - [CThreadPool](https://github.com/ChunelFeng/CThreadPool)
 - [minilog](https://github.com/archibate/minilog)
 - [Golang - net package](https://pkg.go.dev/net)
