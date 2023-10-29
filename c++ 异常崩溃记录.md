
#### munmap_chunk(): invalid pointer
这个错误其实是使用new 申请空间后，再次对申请的空间进行分配，最后释放的时候的多次释放。
原因在于内存读取或写入越界导致释放以及释放了的内存
比如这样一段代码
```cpp
 size_t len = 22
 uint8_t *data[2];
 uint8_t* temp = new uint8_t[len];
 if(temp != nullptr) {
    data[0] = temp;
    data[1] = temp + len / 2;
 }
　/// do something  
 // 释放资源
for(size_t i = 0; i < 2; i++) {
		delete[] data[i];
	   data[i] = nullptr;      
}   
```

上述代码就会报这个错误。

#### double free or corruption (out)

#### free(): invalid pointer

```c++
robot_model_loader::RobotModelLoader robot_model_loader("robot_description");  
auto mRobotModel = robot_model_loader.getModel();  
auto mRobotStatePtr = std::make_shared<robot_state::RobotState>(mRobotModel);  
 mJointModelGroup.reset(mRobotStatePtr->getJointModelGroup(PLANNING_GROUP)); // 此处报错，释放了内存  
mPlanningScene = std::make_shared<planning_scene::PlanningScene>(mRobotModel); // 都调用mRobotModel， 导致二次释放
```

#### boost: mutex lock failed in pthread_mutex_lock: Invalid argument

>This might be due to a callback queue or spinner being destructed before a subscriber get's unsubscribed (or destructed). Hard to say without a code sample.

```c++
class RosInterface {  
public:  
    static void initRosInterface(ros::NodeHandle &nh, const std::string &path);  
  
   static std::unique_ptr<RosServer> mRosServer;  // 析构时报错，
    static std::unique_ptr<RosClient> mRosClient;  
};
```
TODO: 明确是action server 不能设置为static或全局变量吗? static: 报错，全局：报错