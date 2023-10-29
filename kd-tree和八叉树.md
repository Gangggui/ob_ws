
## Kd-tree

### 简介

一种对k维空间中的实例点进行存储以便对其进行快速检索的[树形数据结构](https://baike.baidu.com/item/%E6%A0%91%E5%BD%A2%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/21506701?fromModule=lemma_inlink)。 主要应用于多维空间关键数据的搜索（如：范围搜索和最近邻搜索）。K-D树是二进制空间分割树的特殊的情况。

### 数据结构

k维的二叉树，每个节点都是k维的数据，数据结构为
```c++
struct kdtree {
	Node-data -数据矢量 
	Range     -空间矢量，该节点代表的空间范围
	split     -整数，垂直与分割超平面的方向轴序号
	Left      -Kd树，由位于该节点分割超平面左子空间内所有数据构成
	Right     -Kd树
	parent    -kd树， 父节点
}
```

### 构建

按照某种顺序将无序化的点云进行有序化排列

构建算法：
```cpp
Input:  无序化的点云，维度k
Output：点云对应的kd-tree
Algorithm：
1、初始化分割轴：对每个维度的数据进行方差的计算，取最大方差的维度作为分割轴，标记为r；
2、确定节点：对当前数据按分割轴维度进行检索，找到中位数数据，并将其放入到当前节点上；
3、划分双支：
    划分左支：在当前分割轴维度，所有小于中位数的值划分到左支中；
    划分右支：在当前分割轴维度，所有大于等于中位数的值划分到右支中。
4、更新分割轴：r = (r + 1) % k;
5、确定子节点：
    确定左节点：在左支的数据中进行步骤2；
    确定右节点：在右支的数据中进行步骤2；
```

举例说明：

1. 二维样例：（2,3），（5,4），（9,6），（4,7），（8,1），（7,2）}
	![image.png](http://pic.ganggui.site/img/20221211203257.png)

	2. 初始分割轴：x轴方差大，选x轴
	3. 确定当前节点：在x轴方向找中位数：选择7，即（7, 2）
	4. 划分双支数据：左支{(2,3)，(5,4)，(4,7)}； 右支：{(9,6)，(8,1)}
	5. 更新分割轴：y轴
	6. 确定子节点：左：（5，4）；右：（9，6）
	![image.png](http://pic.ganggui.site/img/20221211203236.png)


### 使用

主要用于两个方面：[[最近邻搜索]]，[[距离方位搜索]]

PCL库里的kdtree

```c++
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>

#include <iostream>
#include <vector>
#include <ctime>

int
main (int argc, char** argv)
{
  srand (time (NULL));

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

  // Generate pointcloud data
  cloud->width = 1000;
  cloud->height = 1;
  cloud->points.resize (cloud->width * cloud->height);

  for (std::size_t i = 0; i < cloud->points.size (); ++i)
  {
    cloud->points[i].x = 1024.0f * rand () / (RAND_MAX + 1.0f);
    cloud->points[i].y = 1024.0f * rand () / (RAND_MAX + 1.0f);
    cloud->points[i].z = 1024.0f * rand () / (RAND_MAX + 1.0f);
  }

  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;

  kdtree.setInputCloud (cloud);

  pcl::PointXYZ searchPoint;

  searchPoint.x = 1024.0f * rand () / (RAND_MAX + 1.0f);
  searchPoint.y = 1024.0f * rand () / (RAND_MAX + 1.0f);
  searchPoint.z = 1024.0f * rand () / (RAND_MAX + 1.0f);

  // K nearest neighbor search

  int K = 10;

  std::vector<int> pointIdxNKNSearch(K);
  std::vector<float> pointNKNSquaredDistance(K);

  std::cout << "K nearest neighbor search at (" << searchPoint.x 
            << " " << searchPoint.y 
            << " " << searchPoint.z
            << ") with K=" << K << std::endl;

  if ( kdtree.nearestKSearch (searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
  {
    for (std::size_t i = 0; i < pointIdxNKNSearch.size (); ++i)
      std::cout << "    "  <<   cloud->points[ pointIdxNKNSearch[i] ].x 
                << " " << cloud->points[ pointIdxNKNSearch[i] ].y 
                << " " << cloud->points[ pointIdxNKNSearch[i] ].z 
                << " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
  }

  // Neighbors within radius search

  std::vector<int> pointIdxRadiusSearch;
  std::vector<float> pointRadiusSquaredDistance;

  float radius = 256.0f * rand () / (RAND_MAX + 1.0f);

  std::cout << "Neighbors within radius search at (" << searchPoint.x 
            << " " << searchPoint.y 
            << " " << searchPoint.z
            << ") with radius=" << radius << std::endl;


  if ( kdtree.radiusSearch (searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0 )
  {
    for (std::size_t i = 0; i < pointIdxRadiusSearch.size (); ++i)
      std::cout << "    "  <<   cloud->points[ pointIdxRadiusSearch[i] ].x 
                << " " << cloud->points[ pointIdxRadiusSearch[i] ].y 
                << " " << cloud->points[ pointIdxRadiusSearch[i] ].z 
                << " (squared distance: " << pointRadiusSquaredDistance[i] << ")" << std::endl;
  }
  return 0;
}
```



## 八叉树（Octree)

### 简介

一种用于描述三维空间的树状结构。八叉树的每个节点表示一个正方体的体积元素，每个节点有八个子节点，将八个子节点所表示的体积元素加在一起就等于父节点的体积。

### 构建

1.将当前的立方体细分为八个子立方体。

2.如果任何一个子立方体内包含多个点，则将其进一步细分为八个子立方体。

3.重复以上操作使得每个子立方体内包含最多一个点。


### 使用

