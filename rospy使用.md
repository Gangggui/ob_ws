
rospy是python的一个模块，位于/opt/ros/xxx/lib/python2.7/dist-packages/rospy中

教程
https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/chapter7/7.1.html


### 1. 基本Api
```python
# 1. 初始化节点
rospy.init_node(name, argv=None, , anonymous=False)

# 2. Topic相关
# Subscriber
rospy.Subscriber(self, name, data_class, call_back=None, queue_size=None)
# Publisher
rospy.Publisher(self, name, data_class, queue_size=None)
publish(self, msg)

# 3. Server相关
#  server
rospy.Servcie(self, name, service_class, handler)
# client
rospy.ServcieProxy(self, name, service_class)

# 4. actionlib相关
# client
client = actionlib.SimpleActionClient(self, name, action_class)
# server 
self.server = actionlib.SimpleActionServer('do_dishes', DoDishesAction, self.execute, False)

# 5. tf相关

```


### 2. Topic

#### 2.1 Publisher

```python
import rospy  
from std_msgs.msg import Int8  
  
  
def msg_pub():  
    publisher = rospy.Publisher('std_test', Int8, queue_size=10)  
    rate = rospy.Rate(1)  
    x = 1  
    while not rospy.is_shutdown():  
        x += 1  
        publisher.publish(Int8(x%8))  
        rate.sleep();  
  
  
if __name__ == '__main__':  
    try:  
        rospy.init_node('fibonacci_client_py')  
        msg_pub()  
    except rospy.ROSInterruptException:  
        print("program interrupted before completion")
```

不同点：
1. rospy创建和初始化一个node，不再需要用NodeHandle。rospy中没有设计NodeHandle 这个句柄，我们创建topic、service等等操作都直接用rospy里对应的方法就行。
2. 消息的创建更加简单，比如gps类型的消息可以直接用类似于构造函数的方 式 gps(state,x,y) 来创建。


#### 2.2 Subscriber

```python
import rospy  
from std_msgs.msg import Int8  
  
  
def msg_callback(Int8):  
    print('recv data is', Int8.data)  
  
  
if __name__ == '__main__':  
    rospy.init_node("listener")  
    rospy.Subscriber("/std_test", Int8, msg_callback)  
    rospy.spin()
```

