
## 1. trac_ik的安装与使用


## 2、ik_fast的安装


#### 2.1 安装依赖

```shell
sudo apt-get install cmake g++ git ipython minizip python-dev python-h5py python-numpy python-scipy qt4-dev-tools
sudo apt-get install libassimp-dev libavcodec-dev libavformat-dev libavformat-dev libboost-all-dev libboost-date-time-dev libbullet-dev libfaac-dev libglew-dev libgsm1-dev liblapack-dev liblog4cxx-dev libmpfr-dev libode-dev libogg-dev libpcrecpp0v5 libpcre3-dev libqhull-dev libqt4-dev libsoqt-dev-common libsoqt4-dev libswscale-dev libswscale-dev libvorbis-dev libx264-dev libxml2-dev libxvidcore-dev

```
1. 问题1：安装依赖出现libjasper-dev无法定位

```shell
sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
sudo apt update
sudo apt upgrade
sudo apt install libjasper1 libjasper-dev
```

#### 2.2 安装OpenSceneGraph-3.4

```shell
sudo apt-get install libcairo2-dev libjasper-dev libpoppler-glib-dev libsdl2-dev libtiff5-dev libxrandr-dev
git clone https://github.com/openscenegraph/OpenSceneGraph.git --branch OpenSceneGraph-3.4
cd OpenSceneGraph
mkdir build; cd build
cmake .. -DDESIRED_QT_VERSION=4
make -j$(nproc)
sudo make install
sudo make isntall_ld_conf
```

#### 2.3 安装FCL 0.5.0

```shell
git clone https://github.com/flexible-collision-library/fcl
cd fcl; git checkout 0.5.0
mkdir build; cd build
cmake ..
make -j `nproc`
sudo make install
```

#### 2.4 安装sympy 0.7.1 

安装前退出anaconda
```shell
pip install --upgrade --user sympy==0.7.1
```

#### 2.5 删除mpmath

```shell
sudo apt remove python-mpmath
```

#### 2.6 安装moveIt! IKFast

```shell

```

#### 2.7 安装openrave

**在安装OpenRAVE前请根据2.5，2.6安装sympy 0.7.1，删除mpmath和安装MoveIt! IKFast。然后安装OpenRAVE：**
```shell
git clone https://github.com.cnpmjs.org/crigroup/openrave-installation
sudo ./install-dependencies.sh
sudo ./install-osg.sh
sudo ./install-fcl.sh
sudo ./install-openrave.sh
```

#### 2.8 配置IKFast

2022.12.07 自定义urdf模型转换dae报段错误
TODO：
- [ ] 基于厂商模型调试IKFast

坐标轴的关系没对准，尤其是后三轴没有符合pipper准则，（三旋转轴交于一点）
因为是solidworks生成的urdf,自己在solidworks里标坐标轴基准轴的时候会出现一点小误差，这里可以到URDF格式里去修改，修改各个joint的<origin里的xyz 和 rpy，（这两个向量分别表示该轴相对于父节点的位姿，rpy对应欧拉角roll pitch yaw）
2，urdf中link的mesh全部使用stl格式的文件表示的，看了github上的一些问题，应该是需要把把urdf描述文件中visual这一块，也就是各个link的geometry，指向.dae格式的文件而不是stl。sw2urdf只能导出stl文件，故可能这里要重新转一组.dae文件
具体解决方法，可以用stl导入meshlab导出.dae，或者用先导出3ds max能用的然后用3ds max导出.dae，再在blender中导出.dae后者用来配准关系和配置颜色。不限于上述方法啊
