- 方法一：同类型厂家设备也有效，固定的是工控机本体的端口号，需要固定设备插入位置
- - 1.查看USB端口信息，找到唯一KERNELS
    - 2.在/etc/udev/rules.d 路径下添加映射文件usb.rules（可取其他名字）
    - 3.重启后生效（重新插拔）
    - 4.代码中打开设备使用时，用 /dev/gps_sensor 打开串口即可
- 方法二：都是不同类型厂家设备时使用，此方法可以*不用固定设备插入的位置*
- - 1.找到自己插入USB设备的ID号
    - 2.在/etc/udev/rules.d 路径下添加映射文件usb.rules（可取其他名字）
    - 3.重启后生效（重新插拔）
    - 4.代码中打开设备使用时，用 /dev/gps_sensor 打开串口即可
- 参考：

---

**前言**

linux系统插入多个USB串口设备时，串口的编号不是固定的，与串口上电的顺序有关。为了解决每次上电顺序不同，或插入顺序不同的问题，可以将USB设备固定到某一端口位置，映射成自己的设备名字。

---

**方法一：同类型厂家设备也有效，固定的是工控机本体的端口号，需要固定设备插入位置**

先看固定方式  
![固定串口插入位置](https://i2.wp.com/img-blog.csdnimg.cn/20201210095615728.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTI1ODMxOA==,size_16,color_FFFFFF,t_70#pic_center)

## 1.查看USB端口信息，找到唯一KERNELS

|   |   |
|---|---|
|1  <br>2  <br>3  <br>4  <br>5  <br>6  <br>7|wjh@wjh_honor:~$ udevadm info --attribute-walk --name=/dev/ttyUSB0 \|grep KERNELS  <br>    KERNELS=="ttyUSB0"  <br>    KERNELS=="1-5:1.0"  <br>    KERNELS=="1-5"  <br>    KERNELS=="usb1"  <br>    KERNELS=="0000:00:14.0"  <br>    KERNELS=="pci0000:00"|

“1-5”这个与硬件本身端口有关，与插入设备无关，可以做标识。

## 2.在/etc/udev/rules.d 路径下添加映射文件usb.rules（可取其他名字）

根据KERNELS 在/etc/udev/rules.d/usb.rules 文件中添加端口映射

|   |   |
|---|---|
|1|wjh@wjh_honor:~$ sudo vim /etc/udev/rules.d/usb.rules|

添加如下代码：

|   |   |
|---|---|
|1|KERNEL=="ttyUSB*",KERNELS=="1-5", MODE:="0777", SYMLINK+="gps_sensor"|

## 3.重启后生效（重新插拔）

查看/dev/ttyUSB*下USB端口是否生效

|   |   |
|---|---|
|1  <br>2  <br>3|wjh@wjh_honor:~$  ls -l /dev \|grep ttyUSB  <br>lrwxrwxrwx  1 root root           7 12月 10 09:42 gps_sensor -> ttyUSB0  <br>crwxrwxrwx  1 root dialout 188,   0 12月 10 09:42 ttyUSB0|

## 4.代码中打开设备使用时，用 /dev/gps_sensor 打开串口即可

---

**方法二：都是不同类型厂家设备时使用，此方法可以_不用固定设备插入的位置_**

## 1.找到自己插入USB设备的ID号

|   |   |
|---|---|
|1  <br>2  <br>3  <br>4  <br>5  <br>6  <br>7  <br>8|wjh@wjh_honor:~$ lsusb  <br>Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub  <br>Bus 001 Device 003: ID 0408:1020 Quanta Computer, Inc.  <br>Bus 001 Device 012: ID 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter//就是这个！  <br>Bus 001 Device 011: ID 2109:2815 VIA Labs, Inc.  <br>Bus 001 Device 008: ID 046d:c542 Logitech, Inc.  <br>Bus 001 Device 004: ID 8087:0aaa Intel Corp.  <br>Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub|

“ID 1a86:7523”这个就是设备ID，**不同厂家**设备ID都不同，唯一标识号，可以做标识。

## 2.在/etc/udev/rules.d 路径下添加映射文件usb.rules（可取其他名字）

根据设备ID号 在/etc/udev/rules.d/usb.rules 文件中添加端口映射

|   |   |
|---|---|
|1|wjh@wjh_honor:~$ sudo vim /etc/udev/rules.d/usb.rules|

添加如下代码：

|   |   |
|---|---|
|1|KERNEL=="ttyUSB*",ATTRS{<!-- -->idVendor}=="1a86", ATTRS{<!-- -->idProduct}=="7523", MODE:="0777", SYMLINK+="gps_sensor"|

## 3.重启后生效（重新插拔）

查看/dev/ttyUSB*下USB端口是否生效

|   |   |
|---|---|
|1  <br>2  <br>3|wjh@wjh_honor:~$  ls -l /dev \|grep ttyUSB  <br>lrwxrwxrwx  1 root root           7 12月 10 09:52 gps_sensor -> ttyUSB0  <br>crwxrwxrwx  1 root dialout 188,   0 12月 10 09:52 ttyUSB0|

## 4.代码中打开设备使用时，用 /dev/gps_sensor 打开串口即可