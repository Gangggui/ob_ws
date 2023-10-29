
[(32条消息) ubuntu(20.04)+linux内核（5.17.3）编译内核_CZAO的博客-CSDN博客_ubuntu 内核编译](https://blog.csdn.net/weixin_62882080/article/details/124260136)
[(32条消息) 小新air14 2020锐龙版Ubuntu18.04亮度无法调节，只能最大亮度，wifi无法联网解决办法_fuck烷基化的博客-CSDN博客](https://blog.csdn.net/weixin_40647655/article/details/109228578)

### 一， linux内核下载

linux内核官方网站：`www.kernel.org`  
进入网站后下载该版本。  
![](https://img-blog.csdnimg.cn/50f7a9c4c9dc4467a3860517f3e4dcf3.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAQ1pBTw==,size_20,color_FFFFFF,t_70,g_se,x_16)

### 二，开始前的准备工作

`输入下面命令完成安装需要的包`

```c
sudo apt-get install  libncurses5-dev   openssl libssl-dev
sudo apt-get install build-essential openssl
sudo apt-get install pkg-config
sudo apt-get install libc6-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install libelf-dev
sudo apt-get install zlibc minizip
sudo apt-get install libidn11-dev libidn11

```

### 三，内核编译

#### 1\. 将下载好的linux内核解压至`/usr/src`

```c
tar -xavf linux-5.17.3.tar.xz  -C  /usr/src
     cd  /usr/src/linux-5.17.3

```

#### 2\. 得到源代码后,将其净化

```cpp
make mrproper 

```

#### 3\. 配置要进行编译的内核

```cpp
 cp /boot/config-`uname -r`  ./.config
 make menuconfig

```

依次点击`load → (.config)OK→ SAVE→ (.config)OK → EXIT load后默认.config (ls -al)`  
![](https://img-blog.csdnimg.cn/29f874d2c2f44c6ab569fba6b591bcf1.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAQ1pBTw==,size_20,color_FFFFFF,t_70,g_se,x_16)

#### 4.编译内核. （15分钟）

`make bzImage -j4` _（-j表示加速，4代表着线程数）_

> 注意，可能会碰到几分钟就编译完了的情况，跑完也不显示什么，直接就完了

![](http://pic.ganggui.site/img/e97f78113df5457b9b40cbfee2abfc99.png)

此时需要我们修改如下文件，使用命令

```shell
gedit .config
```

看了网上好多东西都是这样改动的，在此为了防止小伙伴们踩坑，我直接将/config文件献上，直接CV即可！！！ 
[(32条消息) ubuntu(20.04)+linux内核（5.17.3）的config文件_CZAO的博客-CSDN博客_内核config文件](https://blog.csdn.net/weixin_62882080/article/details/124262374)

#### 5.编译模块.（1小时左右，我电脑好像就用了40min，反正需要等待一定时间）

```shell
 make modules -j4
```

#### 6.安装模块

```shell
make INSTALL_MOD_STRIP=1 modules_install
```

#### 7.打包

这个命令的作用是把/lib/modules/5.18.0中对应的.ko驱动打包到initrd.img文件中。

```csharp
mkinitramfs /lib/modules/5.18.0 -o /boot/initrd.img-5.18.0-generic

```

![](https://img-blog.csdnimg.cn/cd8c5f7af70b42d4bdb057947b8856e2.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAQ1pBTw==,size_20,color_FFFFFF,t_70,g_se,x_16)

#### 8.到此为止,构建内核完毕,把内核映象和System.map拷贝到/boot/下

```shell
sudo cp /usr/src/linux-5.18.0/arch/x86/boot/bzImage    /boot/vmlinuz-5.18.0-generic
sudo cp  /usr/src/linux-5.18.0/System.map    /boot/System.map-5.18.0
```

#### 9\. 修改grub配置文件/boot/grub/grub.cfg

```shell
chmod 777 grub.cfg
update-grub2  
```

![](https://img-blog.csdnimg.cn/ee000279ccb5410eb61b400d81699488.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAQ1pBTw==,size_20,color_FFFFFF,t_70,g_se,x_16)

重启,启动grub时就可看到自己新的内核

> reboot

在终端输入

> uname -r

![](https://img-blog.csdnimg.cn/8b5ce3355faf4f6bbc5ea308b26a33a0.png)

### 四， 更新Firmware

高级模式选择原来的内核进入系统  
更新firmware。  
在https://mirrors.tuna.tsinghua.edu.cn/kernel/firmware/?C=M&O=A下载新版的firmware。  
![](https://img-blog.csdnimg.cn/20201026171653757.png#pic_center)

我下载的是tar.gz格式的文件。  
解压后文件夹目录下进入终端安装，sudo make install，  
![](https://img-blog.csdnimg.cn/20210221170319786.png)

重启，可以进入系统，亮度也可以调节了。  