```cmake
#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## 添加python程序．in contrast to setup.py, you can choose the destination
 install(PROGRAMS
   scripts/talker.py
   scripts/listener.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

## 添加可执行文件或者库文件，Mark executables and/or libraries for installation
 install(TARGETS talker_node listener_node
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

## 添加头文件．Mark cpp header files for installation
 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
   PATTERN ".svn" EXCLUDE
 )
## 添加资源文件的目录，例如文件夹：urdf mesh rviz，其下的所有子目录的文件也会安装到相应的目录下．
 install(DIRECTORY model
            DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
    )
 install(DIRECTORY urdf
            DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
    )
 install(DIRECTORY mesh
            DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
    )
 install(DIRECTORY rviz
            DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
    )
    
## 添加资源文件．Mark other files for installation (e.g. launch and bag files, etc.)
 install(FILES
   launch/bringup.launch
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
 )

# 统一添加
foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
```
