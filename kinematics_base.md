用于计算机械臂正逆运动学的接口基类

#### 参考
https://blog.csdn.net/weixin_44229927/article/details/115964656



#### 头文件依赖
```c++
#include <geometry_msgs/Pose.h>  
#include <moveit_msgs/MoveItErrorCodes.h>  
#include <moveit/macros/class_forward.h>  
#include <ros/node_handle.h>
```

#### 离散化方式

```c++
/*  
 * @enum DiscretizationMethods * * @brief Flags for choosing the type discretization method applied on the redundant joints during an ik query */namespace DiscretizationMethods  
{  
enum DiscretizationMethod  
{  
  NO_DISCRETIZATION = 1, /**< The redundant joints will be fixed at their current value. */  
  ALL_DISCRETIZED,       /**< All redundant joints will be discretized uniformly */  
  SOME_DISCRETIZED, /**< Some redundant joints will be discretized uniformly. The unused redundant joints will be fixed  
                       at their                         current value */  ALL_RANDOM_SAMPLED, /**< the discretization for each redundant joint will be randomly generated.*/  
  SOME_RANDOM_SAMPLED /**< the discretization for some redundant joint will be randomly generated.  
                           The unused redundant joints will be fixed at their current value. */};  
}  // namespace DiscretizationMethods  
typedef DiscretizationMethods::DiscretizationMethod DiscretizationMethod;
```

#### 错误码
```c++
/*  
 * @enum KinematicErrors * @brief Kinematic error codes that occur in a ik query 
 * */
namespace KinematicErrors  
{  
enum KinematicError  
{  
  OK = 1,                              /**< No errors*/  
  UNSUPORTED_DISCRETIZATION_REQUESTED, /**< Discretization method isn't supported by this implementation */  
  DISCRETIZATION_NOT_INITIALIZED,      /**< Discretization values for the redundancy has not been set. See  
                                            setSearchDiscretization(...) method*/  MULTIPLE_TIPS_NOT_SUPPORTED,         /**< Only single tip link support is allowed */  
  EMPTY_TIP_POSES,                     /**< Empty ik_poses array passed */  
  IK_SEED_OUTSIDE_LIMITS,              /**< Ik seed is out of bounds*/  
  SOLVER_NOT_ACTIVE,                   /**< Solver isn't active */  
  NO_SOLUTION                          /**< A valid joint solution that can reach this pose(s) could not be found */  
  
};  
}  // namespace KinematicErrors  
typedef KinematicErrors::KinematicError KinematicError;
```

### 运动学解方式
```c++
/**  
 * @struct KinematicsQueryOptions 
 * @brief A set of options for the kinematics solver 
 * */
struct KinematicsQueryOptions  
{  
  KinematicsQueryOptions()  
    : lock_redundant_joints(false)  
    , return_approximate_solution(false)  
    , discretization_method(DiscretizationMethods::NO_DISCRETIZATION)  
  {  
  }  
  
  bool lock_redundant_joints;                 /**<  KinematicsQueryOptions#lock_redundant_joints. */  
  bool return_approximate_solution;           /**<  KinematicsQueryOptions#return_approximate_solution. */  
  DiscretizationMethod discretization_method; /**<  Enumeration value that indicates the method for discretizing the  
                                                    redundant. joints KinematicsQueryOptions#discretization_method. */};
```

#### ik计算结果
```c++
/*  
 * @struct KinematicsResult
 * @brief Reports result details of an ik query 
 * * 
 * This struct is used as an output argument of the getPositionIK(...) method that returns multiple joint solutions. 
 * It contains the type of error that led to a failure or KinematicErrors::OK when a set of joint solutions is found. 
 * The solution percentage shall provide a ratio of solutions found over solutions searched. 
 * */
 struct KinematicsResult  
{  
  KinematicError kinematic_error; /**< Error code that indicates the type of failure */  
  double solution_percentage;     /**< The percentage of solutions achieved over the total number  
                                       of solutions explored. */};
```

### KinematicsBase类

#### 构造函数
```c++
KinematicsBase::KinematicsBase()  
  : tip_frame_("DEPRECATED")  
  // help users understand why this variable might not be set  
  // (if multiple tip frames provided, this variable will be unset)  , search_discretization_(DEFAULT_SEARCH_DISCRETIZATION)  
  , default_timeout_(DEFAULT_TIMEOUT)  
{  
  supported_methods_.push_back(DiscretizationMethods::NO_DISCRETIZATION);  
}

KinematicsBase::~KinematicsBase() = default;
```

