#### 增加空间

**生成 swapfile 文件操作如下**

- 1. 新增 swapfile 文件大小自定义  
    `sudo fallocate -l 4G /var/swapfile`
- 2. 配置该文件的权限  
    `sudo chmod 600 /var/swapfile`
- 3. 建立交换分区  
    `sudo mkswap /var/swapfile`
- 4. 启用交换分区  
    `sudo swapon /var/swapfile`

![[Pasted image 20231127095853.png]]

#### 设置为自动启用 swapfile

`sudo bash -c 'echo "/var/swapfile swap swap defaults 0 0" >> /etc/fstab'`

增加后如下图：

jtop

![[Pasted image 20231127095819.png]]

  
swap 变成了 8G

### 删除空间

打开之前设置好的启动挂载的 fstab 文件 `sudo vi /etc/fstab` , 注释掉 `#/var/swapfile swap swap defaults 0 0`
![[Pasted image 20231127095841.png]]

重启 `reboot`

启动之后 `sudp rm -rf /var/swapfile` 这样以后增加的 swap 就去掉了