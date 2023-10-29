#ros 

1. ros 时间戳转换成浮点格式
```c++
double time =ros::Time::now().toSec(); //把时间戳转化成浮点型格式
```
2. 浮点格式转换成 ros 时间戳
```c++
odom.header.stamp = ros::Time().fromSec(time); //把浮点型变成时间戳
```
