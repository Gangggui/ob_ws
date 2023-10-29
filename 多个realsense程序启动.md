前提条件：
安装好ROS系统
安装好realsense-ros库
备注：以下方法仅在PC主机上进行了测试，并且自带4个USB3.0接口。

方法1：通过serial_no字段，ROS自动去查找并发布主机上全部realsense相机。

方法2：通过serial_no字段，开发者通过指定相机serial_no编号，发布指定数量的realsense相机。

方法3：通过usb_port_id字段，ROS自动去查找并发布主机上全部realsense相机。

方法4：通过usb_port_id字段，开发者通过指定主机的usb_port_id端口号，发布指定数量的realsense相机。

1 通过serial_no开启4个相机方法
1.1 方法1——自动开启全部realsense相机
如果要使用roslaunch命令开启全部realsense相机，需要修改rs_multiple_devices.launch文件。

如果使用apt安装的realsense-ros，那么该文件路径在/opt/ros/melodic/share/realsense2_camera/launch/rs_multiple_devices.launch。

具体修改rs_multiple_devices.launch文件后的代码如下（如果realsense相机超过4个，新增字段即可开启更多相机）：
```xml
<launch>
<arg name="serial_no_camera1" default=""/> <!-- Note: Replace with actual serial number -->
<arg name="serial_no_camera2" default=""/> <!-- Note: Replace with actual serial number -->
<arg name="serial_no_camera3" default=""/> <!-- Note: Replace with actual serial number -->
<arg name="serial_no_camera4" default=""/>

<arg name="camera1" default="camera1"/> <!-- Note: Replace with camera name -->
<arg name="camera2" default="camera2"/> <!-- Note: Replace with camera name -->
<arg name="camera3" default="camera3"/> <!-- Note: Replace with camera name -->
<arg name="camera4" default="camera4"/>

<arg name="tf_prefix_camera1" default="$(arg camera1)"/>
<arg name="tf_prefix_camera2" default="$(arg camera2)"/>
<arg name="tf_prefix_camera3" default="$(arg camera3)"/>
<arg name="tf_prefix_camera4" default="$(arg camera4)"/>
<arg name="initial_reset" default="false"/>

<group ns="$(arg camera1)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera1)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera1)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera2)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera2)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera2)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera3)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera3)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera3)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera4)" >
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera4)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera4)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

</launch>
```
通过rs_multiple_devices启动全部相机的命令如下：（至于开启多少个相机，与rs_multiple_devices.launch中你定义了多少个serial_no_camera字段有关）

`roslaunch realsense2_camera rs_multiple_devices.launch `

1.2 方法2——自定义开启部分的realsense相机
如果你不想开启主机上所有realsense相机，并且想通过serial_no来指定要开启的相机，那么就修改rs_multiple_devices.launch文件（如果realsense相机超过4个，新增字段即可开启更多相机），如下：

```xml
<launch>
<arg name="serial_no_camera1" default=""/> <!-- Note: Replace with actual serial number -->
<arg name="serial_no_camera2" default=""/> <!-- Note: Replace with actual serial number -->
<arg name="serial_no_camera3" default=""/> <!-- Note: Replace with actual serial number -->
<arg name="serial_no_camera4" default=""/>


<arg name="camera1" default="camera1"/> <!-- Note: Replace with camera name -->
<arg name="camera2" default="camera2"/> <!-- Note: Replace with camera name -->
<arg name="camera3" default="camera3"/> <!-- Note: Replace with camera name -->
<arg name="camera4" default="camera4"/>

<arg name="tf_prefix_camera1" default="$(arg camera1)"/>
<arg name="tf_prefix_camera2" default="$(arg camera2)"/>
<arg name="tf_prefix_camera3" default="$(arg camera3)"/>
<arg name="tf_prefix_camera4" default="$(arg camera4)"/>
<arg name="initial_reset" default="false"/>

<group ns="$(arg camera1)"  if="$(eval serial_no_camera1 != '')">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera1)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera1)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera2)"  if="$(eval serial_no_camera2 != '')">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera2)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera2)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera3)"  if="$(eval serial_no_camera3 != '')">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera3)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera3)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera4)"  if="$(eval serial_no_camera4 != '')">

<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="serial_no" value="$(arg serial_no_camera4)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera4)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

</launch>
```
通过rs_multiple_devices启动指定的一批相机的命令如下：（camera编号换成自己相机编号）

roslaunch realsense2_camera rs_multiple_devices.launch serial_no_camera1:=823112060538 serial_no_camera2:=821312062713 
备注：

查看当前主机插入的realsense相机编号的命令：rs-enumerate-devices | grep Serial


如上图，主机上插了4个realsense相机，使用Serial Number后面的编号。
2 通过usb_port_id开启4个相机方法
该方法原理是ROS自动在指定的主机USB端口号上找realsense相机。

具体方法：修改rs_multiple_devices.launch文件（也可以自己创建一个.launch文件），内容变成如下：

```xml
<launch>
<arg name="usb_port_id1" default="2-5"/>
<arg name="usb_port_id2" default="2-6"/>
<arg name="usb_port_id3" default="2-7"/>
<arg name="usb_port_id4" default="2-8"/>


<arg name="camera1" default="camera1"/> <!-- Note: Replace with camera name -->
<arg name="camera2" default="camera2"/> <!-- Note: Replace with camera name -->
<arg name="camera3" default="camera3"/> <!-- Note: Replace with camera name -->
<arg name="camera4" default="camera4"/>

<arg name="tf_prefix_camera1" default="$(arg camera1)"/>
<arg name="tf_prefix_camera2" default="$(arg camera2)"/>
<arg name="tf_prefix_camera3" default="$(arg camera3)"/>
<arg name="tf_prefix_camera4" default="$(arg camera4)"/>
<arg name="initial_reset" default="false"/>

<group ns="$(arg camera1)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="usb_port_id" value="$(arg usb_port_id1)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera1)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera2)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="usb_port_id" value="$(arg usb_port_id2)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera2)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera3)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="usb_port_id" value="$(arg usb_port_id3)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera3)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

<group ns="$(arg camera4)">
<include file="$(find realsense2_camera)/launch/includes/nodelet.launch.xml">
<arg name="usb_port_id" value="$(arg usb_port_id4)"/>
<arg name="tf_prefix" value="$(arg tf_prefix_camera4)"/>
<arg name="initial_reset" value="$(arg initial_reset)"/>
</include>
</group>

</launch>
```
备注：
上述4个默认default端口号，是测试时4个realsense相机插在主机上的USB端口号。具体使用时，要明确realsense所插主机的USB端口号。查找realsense所插USB端口号方法见realsense-ros官网。
也可以删掉default默认端口号，那执行rs_multiple_devices.launch时ROS会自动在4个主机USB端口上找realsense相机，找到几个就会发布几个相机。这就有个问题，如果rs_multiple_devices.launch中只定义了4个usb_port_id字段，那么它只会在4个USB端口上找，如果主机上有4个以上USB端口，那么该rs_multiple_devices.launch可能无法全部自动的找到所有realsense相机，解决办法就是往rs_multiple_devices.launch中新增usb_port_id字段，使字段数量超过主机USB端口数量，那么该命令就能全部查到所有realsense相机。
如果只想打开固定USB端口上的realsense相机，参考本文“方法1”，删除launch文件中default默认端口号，并在某些位置加上形如： if="$(eval usb_port_id1 != '')"  
