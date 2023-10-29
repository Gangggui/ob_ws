
#程序素材积累

基于c++11 条件变量和libhv库实现

```c++
  
#include "hv/hv.h"  
#include "hv/TcpClient.h"  
#include "Logger.hpp"  
#include <mutex>  
#include <condition_variable>  
  
class TcpSimpleClient {  
public:  
    TcpSimpleClient(const char* ip, int port, int timeout = 500) : ip_(ip), port_(port),  
        time_out_(timeout){  
        m_tcp_client = std::make_shared<hv::TcpClient>();  
        int connect_fd = m_tcp_client->createsocket(port_, ip_.c_str());  
        if (connect_fd < 0) {  
            LOG_E("tcp句柄创建失败");  
            exit(-1);  
        }  
  
        m_tcp_client->onConnection = [this](const hv::SocketChannelPtr& channel) {  
            std::string peer_addr = channel->peeraddr();  
            if (channel->isConnected()) {  
                is_connected.store(true);  
                LOG_I("连接服务器ip {}! connect_fd={}", peer_addr.c_str(), channel->fd());  
            } else {  
                if (is_connected.load()) {  
                    LOG_W("与服务器{}断连! connect_fd={}", peer_addr.c_str(), channel->fd());  
                }  
                is_connected.store(false);  
            }  
        };  
  
        m_tcp_client->onMessage = [this](const hv::SocketChannelPtr& channel, hv::Buffer* buf) {  
            std::string data{};  
            data.insert(recv_buf_.begin(), (char*)buf->data(),  
                                 (char*)buf->data()+(int)buf->size());  
            setRecvBuf(data);  
            cond_.notify_all();  
        };  
  
        // 设置重连参数  
        reconn_setting_t reconnect_param;  
        reconn_setting_init(&reconnect_param);  
        reconnect_param.min_delay = 1000;  
        reconnect_param.max_delay = 10000;  
        reconnect_param.delay_policy = 2;  
        m_tcp_client->setReconnect(&reconnect_param);  
    }  
  
    bool Send(const std::string &send_data, std::string &recv_data) {  
        std::unique_lock<std::mutex> lock(mutex_);  
  
        if (!is_connected.load()) {  
            LOG_I("tcp未连接");  
            return false;        }  
  
        m_tcp_client->send(send_data);  
        if (cond_.wait_for(lock,std::chrono::milliseconds(time_out_))  
            == std::cv_status::timeout) {  
            LOG_W("tcp超时未返回");  
            return false;        }  
        recv_data = getRecvBuf();  
        return true;    }  
  
    std::string getRecvBuf() {  
        std::unique_lock<std::mutex> lock(recv_mutex);  
        return recv_buf_;  
    }  
  
    bool getConnected() {  
        return is_connected;  
    }  
private:  
    std::shared_ptr<hv::TcpClient> m_tcp_client;  
    std::atomic_bool is_connected{false};  
    std::string ip_{};  
    int port_;  
    std::mutex mutex_;  
    std::condition_variable cond_;  
    int time_out_ = 500;  
    std::string recv_buf_{};  
    std::mutex recv_mutex;  
  
    void setRecvBuf(const std::string &data) {  
        std::unique_lock<std::mutex> lock(recv_mutex);  
        recv_buf_ = data;  
    }  
};
```