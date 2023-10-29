### 测试文件


```python
import numpy as np
import cv2
import matplotlib.pyplot as plt
```

```python
img = cv2.imread("000.png")
plt.figure()
plt.imshow(img)
plt.show()

```

```python
gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

plt.imshow(gray)
plt.show()
```


```python
obj_bin_raw = cv2.inRange(gray, lowerb=210, upperb=255)
plt.imshow(obj_bin_raw)
plt.show()
```


```python
# 形态学处理
kernel = np.ones((3,3), np.uint8)
obj_bin = cv2.erode(obj_bin_raw, kernel, iterations=1)
# 膨胀
kernel = np.ones((4,4),np.uint8)
obj_bin = cv2.dilate(obj_bin, kernel, iterations=1)
plt.imshow(obj_bin)
plt.show()
```


```python
contours, hies = cv2.findContours(obj_bin, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_TC89_L1)
print(f"联通个数 {len(contours)}")
```


```python
AREA_THRESHOLD = 500

# s声明画布，拷贝至img
canvas = np.copy(img)
obj_rect_cnt_list = []
for cidx,cnt in enumerate(contours):
    x, y, w, h = cv2.boundingRect(cnt)
    # 根据面积来判断是否
    if w*h < AREA_THRESHOLD:
        continue
    min_area_rect = cv2.minAreaRect(cnt)
    print("hello")
    
    # 将浮点数转为整数
    rect_contour = np.int64(cv2.boxPoints(min_area_rect))
    obj_rect_cnt_list.append(rect_contour)
    cv2.drawContours(canvas, [rect_contour], 0, (0,255,0), 5)
plt.imshow(canvas[:, :, ::-1])
```


```python
def random_color():
    # 随机生成颜色
    return [np.random.randint(0, 256) for i in range(3)]


def get_obj_mask(img_w, img_h, obj_rect_cnt):
    mask = np.zeros((img_h, img_w)).astype('uint8')
    cv2.drawContours(mask, [obj_rect_cnt], 0, 255, -1)
    mask = cv2.bitwise_and(mask, obj_bin_raw)
    return mask

obj_mask_color = np.zeros_like(canvas)
for obj_rect_cnt in obj_rect_cnt_list:
    cv2.drawContours(obj_mask_color, [obj_rect_cnt], 0, random_color())
    
plt.imshow(obj_mask_color[:, :, ::-1])
```


```python
# 联通域
obj_rect_cnt = obj_rect_cnt_list[0]
img_h, img_w = img.shape[:2]
mask = get_obj_mask(img_w, img_h, obj_rect_cnt)

plt.imshow(mask)
```


```python
## 3d 图像处理
# 载入数据
model_pcd = o3d.io.read_point_cloud("data.pcd")
model_pcd.paint_uniform_color([1,0,0])
# 显示模型点云
corrd_mesh = o3d.geometry.TriangleMesh.create_coordinate_frame()
corrd_mesh = corrd_mesh.scale(20, center=(0,0,0))
o3d.visualization.draw_geometries([model_pcd, corrd_mesh])

def get_pcd(img, pmap, img_mask=None):
    if img_mask is None:
        h, w_ = img.shape
        valid_pixel_index = np.bool8(np.ones((h,w)).reshape(-1))
    else:
        valid_pixel_index = (img_mask != 0).reshape(-1)
    # 将图像转换未RGB色彩空间， 并将数值缩放到【0，1】之间
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB).reshape(-1,3)/255.0
    # 将点云转换列向量
    pmap = pmap.reshape(-1,3)
    # 有效索引
    valid_pixel_index = np.bitwise_and(~np.isnan(pmap[:, -1]), valid_pixel_index)
    # 获取有效点云与像素
    pmap_valid = pmap[valid_pixel_index]
    img_valid = img[valid_pixel_index]
    # 创建pcd对象
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(pmap_valid)
    pcd.colors = o3d.utility.Vector3dVector(img_valid)
    return pcd

# 载入点云映射
img_h, img_w, channel = img.shape
pmap = np.loadtxt("./data/test.xyz", delimiter=",")
pmap = pmap.reshape((img_h, img_w, 3))
# 单位转为mm
pmap *= 1000
ws_pcd = get_pcd(img. pmap)

o3d.visualization.draw_geometries([ws_pcd])
obj_pcd = get_pcd(img, pmap, img_mask=mask)
o3d.visualization.draw_geometries([obj_pcd])
```


```python
## 工件位姿估计v1
def draw_registration_result(source, target, transformation):
    source_temp = copy.deepcopy(source)
    target_temp = copy.deepcopy(target)
    # 模板点云绘制颜色
    source_temp.paint_uniform_color([1,0,0])
    # 变换点云
    source_temp.transform(transformation)
    # 物体点云绘制颜色
    target_temp.paint_uniform_color([0, 1, 0])
    # 物体坐标系
    obj_corrd_mesh = o3d.geometry.TriangleMesh.create_coordinate_frame
    obj_corrd_mesh = obj_corrd_mesh.scale(20, center=(0,0,0))
    obj_corrd_mesh.transform(transformation)
    # 相机坐标系(左侧)
    cam_corrd_mesh = o3d.geometry.TriangleMesh.create_coordinate_frame
    # 可视化
    o3d.visualization.draw_geometries([source_temmp target_temp, obj_width=800, height=800])
```


```python
def obj_pose_estimate(img, pmap, mask,model_pcd,is_downsample=False):
    # 获取物体的人点云
    obj_pcd = get_pcd(img, pmap, img_mask=mask)
    if is_downsample:
        # 物体点云降采样
        obj_pcd_downsample = obj_pc.voxel_down_sample(voxel_size=1)
        # 计算点云的法向量
        # 估计法向量
        obj_pcd_downsample.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHy
                                           brid(radius=))
     # ICP点云配准
    source = model_pcd
    if is_downsample:
        target = obj_pcd_downsample
    else:
        target = obj_pcd
    threshold = 10
    # 初始化矩阵，平移向量为物体PCD的质心
    trans_init = np.eye(4)
    trans_init[:3, 3] = obj_pcd.get_center()
    #旋转矩阵让初始z轴与物体z轴共线取反
    trans_init[:3, :3] = Geometry.euler2rmat([np.pi, 0, 0])
    reg_p2p = o3d.pipelines.registration.registration_icp(
        source, target, threshold, trans_init,
    o3d.pipelines.registration.TransformationEstimationPointToPoint,
    o3d.pipelines.registration.ICPConvergenceCriteria(max_iteration=10))
    T_cam2obj = reg_p2p.transformation
    return T_cam2obj, source, target

    
T_cam2obj, source, target = obj_pose_estimate(img, pmap, mask, model_pcd)
draw_registration_result(source,  target, T_cam2obj)
```


```python
## 获取工作台的点云
ws_pcd = get_pcd(img. pmap)

```
