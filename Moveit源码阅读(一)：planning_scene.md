
### 构造函数

```c++
  
PlanningScene::PlanningScene(const robot_model::RobotModelConstPtr& robot_model,  
                             const collision_detection::WorldPtr& world)  
  : robot_model_(robot_model), world_(world), world_const_(world)  
{  
  initialize();  
}  
  
PlanningScene::PlanningScene(const urdf::ModelInterfaceSharedPtr& urdf_model,  
                             const srdf::ModelConstSharedPtr& srdf_model, const collision_detection::WorldPtr& world)  
  : world_(world), world_const_(world)  
{  
  if (!urdf_model)  
    throw moveit::ConstructException("The URDF model cannot be NULL");  
  
  if (!srdf_model)  
    throw moveit::ConstructException("The SRDF model cannot be NULL");  
  
  robot_model_ = createRobotModel(urdf_model, srdf_model);  
  if (!robot_model_)  
    throw moveit::ConstructException("Could not create RobotModel");  
  
  initialize();  
}
```