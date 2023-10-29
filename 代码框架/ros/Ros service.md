
Q: ros service 发生堵塞时，主线程是否会堵塞
A: 会堵塞
```C++
#include "ros/ros.h"  
#include "std_srvs/SetBool.h"  
  
bool myServiceCallback(std_srvs::SetBool::Request& req,  
                       std_srvs::SetBool::Response& res) {  
    ROS_INFO("Received request: ");  
    sleep(10);  
    return true;  
}  
  
int main(int argc, char** argv) {  
    // 初始化 ROS 节点  
    ros::init(argc, argv, "my_service_server");  
  
    // 创建 ROS 句柄  
    ros::NodeHandle nh;  
  
    // 创建 ROS 服务服务器  
    ros::ServiceServer server = nh.advertiseService("my_service", myServiceCallback);  
      
    ros::Rate r(2);  
    while (ros::ok()) {  
        ROS_INFO("Ready to receive requests.");  
        ros::spinOnce();  
        r.sleep();  
    }  
    return 0;  
}
```
多线程情况下用
```c++
#include "ros/ros.h"  
#include "std_srvs/SetBool.h"  
#include "thread"  
bool myServiceCallback(std_srvs::SetBool::Request& req,  
                       std_srvs::SetBool::Response& res) {  
    ROS_INFO("Received request: ");  
    std::cout << "server thread id is:" << std::this_thread::get_id() << std::endl;  
    sleep(10);  
    return true;  
}  
  
int main(int argc, char** argv) {  
    // 初始化 ROS 节点  
    ros::init(argc, argv, "my_service_server");  
  
    // 创建 ROS 句柄  
    ros::NodeHandle nh;  
    ros::AsyncSpinner spinner(2);  
    spinner.start();  
    // 创建 ROS 服务服务器  
    ros::ServiceServer server = nh.advertiseService("my_service", myServiceCallback);  
  
    ros::Rate r(2);  
    while (ros::ok()) {  
        std::cout << "this thread id is:" << std::this_thread::get_id() << std::endl;  
        ros::spinOnce();  
        r.sleep();  
    }  
    return 0;  
}
```

Q: ros serviceClient 改成不堵塞形式
A: 基于std::future实现
```c++
#include <future>  
#include "ros/ros.h"  
#include "std_srvs/SetBool.h"  
  
template<class T, class REQ, class RES>  
class ServiceClient {  
public:  
    explicit ServiceClient(ros::NodeHandle &nh_, std::string service_name="/my_service") {  
        // 创建 ROS 服务客户端  
        client_ = nh_.serviceClient<T>(service_name);  
    }  
  
    bool isDataReady() {  
        return mFut.valid() && mFut.wait_for(std::chrono::microseconds (10))  
                == std::future_status::ready;  
    }  
  
    bool getData(RES &data) {  
        if (mFut.valid()) {  
            data = mFut.get();  
            return true;  
        }  
        return false;  
    }  
  
    bool call(const REQ &req) {  
        // 创建请求  
  
        if (mFut.valid()) {  
            printf("已有数据未get");  
            return false;  
        }  
        mFut = std::async([&]() -> RES {  
            client_.waitForExistence(ros::Duration(3));  
            std::this_thread::sleep_for(std::chrono::seconds(3));  
            RES res;  
            client_.call(req, res);  
            return res;  
        });  
        return true;  
    }  
  
private:  
    ros::ServiceClient client_;  
    std::future<RES> mFut;  
};  
  
using BoolService = ServiceClient<std_srvs::SetBool, std_srvs::SetBoolRequest, std_srvs::SetBoolResponse>;  
int main(int argc, char** argv) {  
    // 初始化 ROS 节点  
    ros::init(argc, argv, "my_service_client");  
    ros::NodeHandle nh;  
    // 创建服务客户端  
    BoolService client(nh);  
    std::cout << client.isDataReady() <<std::endl;  
    // 发送请求  
    std_srvs::SetBoolRequest req;  
    client.call(req);  
  
    // 等待响应  
    ros::Rate r(2);  
    while (ros::ok()) {  
        std::cout << "this thread id is:" << std::this_thread::get_id() << std::endl;  
        if (client.isDataReady()) {  
            std_srvs::SetBool::Response data;  
            if (client.getData(data)) {  
                ROS_INFO("Received response: %d", data.success);  
            }  
        }  
        ros::spinOnce();  
        r.sleep();  
    }  
    return 0;  
}
```

