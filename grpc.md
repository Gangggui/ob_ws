
### 简单模式（Simple RPC）

-   这种模式基于传统的http/1.0模式，即客户端发起一次请求，服务端响应一个数据，这和普通的RPC没有什么区别

### 服务端数据流模式（Server-side streaming RPC）

-   这种模式是客户端发起一次请求，类似于 “订阅” 模式，服务端返回一段连续的数据流。
-   典型的例子是客户端向服务端发送一个股票代码，服务端就把该股票的实时数据源源不断的返回给客户端。

### 客户端数据流模式（Client-side streaming RPC）

-   与服务端数据流模式相反，这次是客户端源源不断的向服务端发送数据流，而在发送结束后，由服务端返回一个响应。
-   典型的例子是物联网终端向服务器报送数据。

### 双向数据流模式（Bidirectional streaming RPC）

-   这是客户端和服务端都可以向对方发送数据流，这个时候双方的数据可以同时互相发送，也就是可以实现实时交互。
-   典型的例子是聊天机器人。

 对于异步通讯的grpc服务器来说，队列只临时缓存一个任务，如果这个任务被执行完毕，那么就会被从队列中清空。  
      * 如果想要继续进行这个相同的任务，就必须再次执行注册服务。  
      * grpc中的注册服务，都是调用 service.RequestXXX() 来完成的。（XXX 就是你在proto中定义的 rpc 方法）  
```c++
void* tag;  // 通过 new 关键字，实例化出你自己的 service 对象  
grpc::ServerContext ctx;    // ServerContext允许代码实现服务处理程序：  
grpc::ServerAsyncReaderWriter<test_pkg::Response, test_pkg::Request> async_rw;  
service.Requesttest(&ctx, &async_rw, cq_.get(), cq_.get(), tag);
```

#### 监听任务队列
```c++
// tag为本次任务的标识，grpc队列内部使用 tag 标签来标记客户端句柄，同一个tag的不同请求，都来自于相同的客户都安  
// tag 可以在你的应用程序内部的线程之间进行传递，方便你异步处理业务  
void* tag = NULL;  
bool ok = false;  
bool res = cq_->Next(&tag, &ok);
grpc::test_pkg::Request req;  
grpc::test_pkg::Response rsp;  
async_rw.Read(&req, tag);   // 流式读取数据  
async_rw.Write(rsp, tag;    // 流式发送数据
```
需要注意的是，当我们使用 grpc::ServerAsyncReaderWriter::Write() 函数进行给客户端回写数据时，消息队列会再次返回，因此我们可以在应用程序中，添加一个状态，来记录当前的操作是客户端发送的，还是 Write 产生的，否则 grpc 内部的断言assert会失败。

Tri-state return for AsyncNext: SHUTDOWN, GOT_EVENT, TIMEOUT.