#### 1. 获取单帧ros topic话题

	以订阅话题“/hello”，消息类型为std_msgs::String为例子

```c++
#include <boost/share_ptr.hpp>
#include <std_msgs/String.h>
#include <ros/ros.h>

int main(int argc, char **argv){
	ros::init("sub_test", argc, argv);
	boost::shared_ptr<std_msgs::String const> msg;

	/*
	boost::shared_ptr<M const> ros::topic::waitForMessage(	const std::string & 	topic, ros::Duration timeout) 
	功能：获取一帧话题
	参数：
		topic: 订阅的话题名
		timeout: 最长等待时间
	返回: 超时没有订阅到话题则返回 NULL
		 成功获取到消息则返回该消息
	http://docs.ros.org/en/diamondback/api/roscpp/html/namespaceros_1_1topic.html
	*/
	msg = ros::topic::waitForMessage<std_msgs::String>("hello", ros::Duration(0.5));
	if(msg!=NULL){//必须要判断，否则为NULL时调用该消息的成员会core dump
		std::cout<<msg->data<<std::endl;
	}
	return 0;
}
```

