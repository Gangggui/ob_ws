机器人型号：sg200
Linux上使用CAN通信的方法
https://www.jianshu.com/p/75db013fa3b7
qweqeeq
#### 配置can口
>https://blog.csdn.net/weifengdq/article/details/103093111#JetsonAGX_Xavier_CAN_17

https://blog.csdn.net/weifengdq/article/details/113846574
#### 创建虚拟can口用于测试
https://blog.csdn.net/ouguangqian/article/details/125217578
```shell
# 安装busybox, 需要里面的devmem工具
sudo apt install busybox

# 用devmem修改寄存器
sudo busybox devmem 0x0c303000 32 0x0000C400
sudo busybox devmem 0x0c303008 32 0x0000C458
sudo busybox devmem 0x0c303010 32 0x0000C400
sudo busybox devmem 0x0c303018 32 0x0000C458

# 安装CAN控制器并加载驱动程序
sudo modprobe can
sudo modprobe can_raw
sudo modprobe mttcan

# 配置前先关闭
sudo ip link set down can1

sudo ip link set can0 type can bitrate 1000000 sample-point 0.8 dbitrate 5000000 dsample-point 0.75 fd on restart-ms 100


# 启动CAN
sudo ip link set up can1

# 打开一个接收终端用于CAN接收
candump can1

# 再打开一个接收终端用于CAN发送
cansend can1 A234567F#99.95.42.07.2B.96.66.6E

```

### 最终使用版本
https://blog.csdn.net/weifengdq/article/details/113846574#:~:text=sudo%20systemctl%20daemon-reload%20sudo%20systemctl,enable%20canfd.service%20sudo%20systemctl%20start%20canfd.service

### 测试日志

linux socketcat 程序杀死后，控制字6041在位置模式下进入追踪错误模式(谐波电机)