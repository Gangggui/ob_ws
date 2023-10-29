---
sr-due: 2023-01-04
sr-interval: 3
sr-ease: 250
---

#review #flashcards/ros/launch #ros 



1. 明白不同标签所起的作用
2. 明白roslaunch加载其他文件的路径
3. 明白roslaunch参数的决定性因素


### 第一个标签 

```xml
<?xml version="1.0"?>
```

### 节点标签`<node>`
```xml
<node name="move_group" launch-prefix="$(arg launch_prefix)" pkg="moveit_ros_move_group" type="move_group" respawn="false" output="screen" args="$(arg command_args)">
```

1. pkg项::指定节点所在的包名，
2. type项::指定可执行程序名字，其与CMakeLists.txt中add_executable()项对应，
3. name项::对应节点启动之后的名字，可使用rosnode list查看
4. respawn项::可选，表示节点退出后，是否重新启动，默认为false。
5. output项::可选，表示log输出位置，如果是screen表示log输出到屏幕，如果是log表示输出到log文件，默认为log。
6. required项::“true | false” (可选)，该节点是否必须，如果为 true,那么如果该节点退出，将杀死整个 roslaunch
7. ns项::“xxx” (可选)，在指定命名空间 xxx 中启动节点
8. args项::“xxx xxx xxx” (可选)，将参数传递给节点
<!--SR:!2023-01-02,1,230-->

### 参数标签1`<param>`
定义一个将要被设置到参数服务器的参数，它的参数值可以通过文本文件、二进制文件或命令等属性来设置，另外 **param 标签可以嵌入到 node 标签**中，以此来作为该 node 的私有参数。
1. 基本用法如下：

```xml
<param name="publish_frequency" type="double" value="10.0">
```
-   name：参数名称 publish_frequency
-   type：参数类型 double，str，int，bool，yaml
-   value：参数值 10.0
2. 嵌入到node标签中，等价于使用<group></group>标签，<group>中的命名空间=node标签的name项


### 参数标签2`<rosparam>`
rosparam 标签允许节点从参数服务器上 load、dump 和 delete YAML 文件
常见用法如下：

```xml
# 参数较多使用 yaml 文件
<rosparam command="load" file="$(find rosparam)/example.yaml">
<rosparam command="delete" param="my/param">

# 传递数组
<rosparam param="a_list">[1, 2, 3, 4]</rosparam>

<rosparam>
    a: 1
    b: 2
</rosparam>

<arg name="whitelist" default="[3, 2]"/>
<rosparam param="whitelist" subt_value="True">$(arg whitelist)</rosparam>
```

-   command项::load，dump，delete三种选项，delete需在load后使用
-   file项::参数文件的路径
-   param::参数名称
-   subt_value::是否允许在 YAML 中替换参数



### env标签

env 标签可以在启动的节点上设置环境变量，这个标签基本只会使用在 launch、include、node、machine 这 4 个标签内部，当使用在 launch 内部时，env 设置的环境标量会应用到内部定义的节点。

常见用法如下：

```xml
<env name="ENV_EXAMPLE" value="some value" />
```

-   name：环境变量名称
-   value：环境变量值


### arg标签

arg 标签表示启动参数，该标签允许创建更多可重用和可配置的启动文件，其可以通过命令行、include 标签、定义在高级别的文件这 3 种方式配置值。

arg 标签声明的参数不是全局的，只能在声明的单个启动文件中使用，可以当成函数的局部参数来理解。

常见用法如下：

```text
# 1. 命令行传递启动参数
roslaunch my_file.launch my_arg:=my_value
# 2. 定义时赋值
<arg name="arg_name" default="arg_name">
<arg name="arg_name" value="arg_name">
```

这两者有点区别，**命令行传递的 arg 参数可以覆盖 default，但不能覆盖 value。**

```xml
# 3. 通过 launch 文件传递参数，覆盖默认值

# my_file.launch
<include file="include.launch">
    <arg name="hoge" value="fuga">
</include>

# include.launch
<launch>
    <arg name="hoge2" value=$(arg hoge)>
    <arg name="hoge" default="false" />
</launch>
```

注意 arg 和 param 标签的区别：

-   arg：启动时参数，只在启动文件 launch 中有意义
-   param：运行时参数，存储在参数服务器中


