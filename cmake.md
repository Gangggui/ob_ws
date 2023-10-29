


### 1. 参考资料
https://zhuanlan.zhihu.com/p/367808125
https://blog.csdn.net/weixin_45590473/article/details/122608048


### 001, 如何在编译时拷贝特定文件到指定路径下
add_custom_command

1.**配合 `add_custom_target` 使用，该命令生成 `add_custom_target` 的依赖；**
```python
add_custom_command(OUTPUT output1 [output2 ...]
                   COMMAND command1 [ARGS] [args1...]
                   [COMMAND command2 [ARGS] [args2...] ...]
                   [MAIN_DEPENDENCY depend]
                   [DEPENDS [depends...]]
                   [BYPRODUCTS [files...]]
                   [IMPLICIT_DEPENDS <lang1> depend1
                                    [<lang2> depend2] ...]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [DEPFILE depfile]
                   [JOB_POOL job_pool]
                   [VERBATIM] [APPEND] [USES_TERMINAL]
                   [COMMAND_EXPAND_LISTS])
```
- OUTPUT：指定命令预期生成的输出文件。3.20版本以后，输出参数可使用一组受限的生成器表达式。
- COMMAND：指定生成时要执行的命令行。
- MAIN_DEPENDENCY：指定命令的主输入源文件。类似于DEPENDS。
- DEPENDS：指定命令所依赖的文件。
- BYPRODUCTS：指定命令预期生成的文件，但其修改时间可能比依赖项的新，也可能不比依赖项的新。
- IMPLICIT_DEPENDS：请求扫描输入文件的隐式依赖项。此选项不能与DEPFILE选项同时指定。
- WORKING_DIRECTORY：指定在何处执行命令。
- COMMENT：指定在生成时执行命令之前显示的消息。
- DEPFILE：指定保存自定义命令依赖项的depfile。它通常由自定义命令本身发出。仅当生成器支持此关键字时，才能使用此关键字。
- JOB_POOL：为Ninja生成器指定一个池。
- VERBATIM：对于构建工具，命令的所有参数都将被正确转义，以便被调用的命令接收到的每个参数不变。请注意，在add_custom_command甚至看到参数之前，CMake语言处理器仍然使用一级转义。建议使用VERBATIM，因为它可以保证正确的行为。如果不指定VERBATIM，则行为是依赖于平台的，因为CMake没有针对于特定工具中特殊字符的保护措施。
- APPEND：将COMMAND和DEPENDS 附加到第一个指定输出的自定义命令。
- USES_TERMINAL：如果可能，该命令将被授予直接访问终端的权限。
- COMMAND_EXPAND_LISTS：命令参数中的列表将展开，包括使用生成器表达式创建的列表。

例子：
```cmake
 cmake_minimum_required(VERSION 3.5)
 ​
 project(test)
 ​
 add_executable(${PROJECT_NAME} main.c)
 ​
 add_custom_command(OUTPUT printout #生成一个名叫 `printout` 的“文件”（该文件不可见），其代表下方的 `COMMAND` 命令；
                    COMMAND ${CMAKE_COMMAND} -E echo compile finish
                    VERBATIM
                   )
 ​
 add_custom_target(finish   #cmake 增加了一个finish目标
                   DEPENDS printout
   )
   
```

2. **单独使用。在生成目标文件（使用 `add_executable()` 或 `add_library()` 命令生成的文件）时自动执行 `add_custom_command` 指定的命令。**
```cmake
```cmake
 add_custom_command(TARGET <target>
                    PRE_BUILD | PRE_LINK | POST_BUILD #分别表示编译之前执行命令，链接之前执行命令，生成目标文件后执行命令；
                    COMMAND command1 [ARGS] [args1...]
                    [COMMAND command2 [ARGS] [args2...] ...]
                    [BYPRODUCTS [files...]]
                    [WORKING_DIRECTORY dir]
                    [COMMENT comment]
                    [VERBATIM] [USES_TERMINAL]
                    [COMMAND_EXPAND_LISTS])
#exampl
 add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E echo compile finish
                    VERBATIM
                   )
```

CMAKE_COMMAND 支持的命令
```shell
Available commands: 
  capabilities              - Report capabilities built into cmake in JSON format
  cat <files>...            - concat the files and print them to the standard output
  chdir dir cmd [args...]   - run command in a given directory
  compare_files [--ignore-eol] file1 file2
                              - check if file1 is same as file2
  copy <file>... destination  - copy files to destination (either file or directory)
  copy_directory <dir>... destination   - copy content of <dir>... directories to 'destination' directory
  copy_if_different <file>... destination  - copy files if it has changed
  echo [<string>...]        - displays arguments as text
  echo_append [<string>...] - displays arguments as text but no new line
  env [--unset=NAME]... [NAME=VALUE]... COMMAND [ARG]...
                            - run command in a modified environment
  environment               - display the current environment
  make_directory <dir>...   - create parent and <dir> directories
  md5sum <file>...          - create MD5 checksum of files
  sha1sum <file>...         - create SHA1 checksum of files
  sha224sum <file>...       - create SHA224 checksum of files
  sha256sum <file>...       - create SHA256 checksum of files
  sha384sum <file>...       - create SHA384 checksum of files
  sha512sum <file>...       - create SHA512 checksum of files
  remove [-f] <file>...     - remove the file(s), use -f to force it (deprecated: use rm instead)
  remove_directory <dir>... - remove directories and their contents (deprecated: use rm instead)
  rename oldname newname    - rename a file or directory (on one volume)
  rm [-rRf] <file/dir>...    - remove files or directories, use -f to force it, r or R to remove directories and their contents recursively
  sleep <number>...         - sleep for given number of seconds
  tar [cxt][vf][zjJ] file.tar [file/dir1 file/dir2 ...]
                            - create or extract a tar or zip archive
  time command [args...]    - run command and display elapsed time
  touch <file>...           - touch a <file>.
  touch_nocreate <file>...  - touch a <file> but do not create it.
  create_symlink old new    - create a symbolic link new -> old
  create_hardlink old new   - create a hard link new -> old
  true                      - do nothing with an exit code of 0
  false                     - do nothing with an exit code of 1
```

#### add_custom_target()
`cmake` 本身支持两种目标文件：可执行程序（由 `add_executable()` 生成）和库文件（由 `add_library()` 生成）。使用 `add_custom_target` 可添加**自定义目标文件**，用于执行某些指令
```cmake
add_custom_target(Name [ALL] [command1 [args1...]]
                   [COMMAND command2 [args2...] ...]
                   [DEPENDS depend depend depend ... ]
                   [BYPRODUCTS [files...]]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [JOB_POOL job_pool]
                   [VERBATIM] [USES_TERMINAL]
                   [COMMAND_EXPAND_LISTS]
                   [SOURCES src1 [src2...]])
   #example
   # 拷贝文件到系统路径下
add_custom_target(finish  
	COMMAND ${CMAKE_COMMAND} -E copy  
	${PROJECT_SOURCE_DIR}/config/config.yaml  
	$ENV{ROBOT_HOME}  
	)
```
`ALL`：在使用 `add_executable` 或 `add_library` 生成目标文件时，默认不会“生成”该命令的目标文件，需要使用命令 `cmake --target <Name>` “生成”。但是如果指定了该参数，那么在生成上述目标文件时也会“生成”`add_custom_target`指定的目标文件；

`example`
```cmake
# 拷贝依赖库到可执行文件目录  
file(GLOB THIRD_LIBS  
        ${PROJECT_SOURCE_DIR}/lib/*.so)  
add_custom_command(TARGET ${PROJECT_NAME}  
        POST_BUILD  
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  
        ${THIRD_LIBS}  
        $<TARGET_FILE_DIR:${PROJECT_NAME}>  
        )  
  
file(GLOB CONFIG_FILES  
        ${PROJECT_SOURCE_DIR}/config/*)  
set(SAVE_CONFIG_PATH $ENV{ROBOT_HOME}/$ENV{DEPLOY_ID}/conf/${PROJECT_NAME})  
if(NOT EXISTS ${SAVE_CONFIG_PATH})  
    file(MAKE_DIRECTORY ${SAVE_CONFIG_PATH})  
endif()  
# 在指定执行文件编译前拷贝配置到指定路径下  
add_custom_command(TARGET ${PROJECT_NAME}  
        POST_BUILD  
        COMMAND ${CMAKE_COMMAND} -E copy  
        ${CONFIG_FILES}  
        ${SAVE_CONFIG_PATH}  
        VERBATIM  
        )  
# 手动更新配置到指定路径  
add_custom_target(UpdateConfig  
        COMMAND ${CMAKE_COMMAND} -E copy  
        ${CONFIG_FILES}  
        ${SAVE_CONFIG_PATH}  
        )
```

## 002 文件管理 （file）

>https://juejin.cn/post/6844903634170298382
#### 文件收集（GLOB）
```cmake
file(GLOB <variable> [LIST_DIRECTORIES true|false] [RELATIVE <path>] [<globbing-expressions>...]) 
# GLOB命令将所有匹配`<globbing-expressions>`（可选,假如不写，毛都匹配不到）的文件挑选出来，默认以字典顺序排序。
file(GLOB files *) 
# LIST_DIRECTORIES设置为false --- 不输出文件夹
file(GLOB files LIST_DIRECTORIES false *)
# 相对路径：设置相对路径为当前文件夹的上级文件夹
file(GLOB files LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/.. *)
# example


file(GLOB_RECURSE <variable> [FOLLOW_SYMLINKS] [LIST_DIRECTORIES true|false] [RELATIVE <path>] [<globbing-expressions>...])
```
>cmake官方不推荐使用GLOB来收集文件，因为在工程或者模块中的CMakeLists.txt文件未更改而用file搜寻的文件夹下有文件的删除或者增加，cmake构建并不会知晓，而是使用旧的list。


## 003 cmakelist传参到c++程序中
在CMakeLists.txt文件中，您可以使用`set`命令来定义变量。以下是一个示例：
```cmake
# 定义变量

set(MY_VARIABLE "Hello, world!")

# 将变量传递给C++程序

add_definitions(-DMY_VARIABLE="${MY_VARIABLE}")
```
在这个例子中，我们使用`set`命令定义了一个名为`MY_VARIABLE`的变量，并将其设置为字符串`"Hello, world!"`。然后，我们使用`add_definitions`命令将该变量传递给C++程序，使用`-D`选项将变量定义为预处理器宏。在C++程序中，您可以使用`#ifdef`和`#ifndef`指令来检查该宏是否已定义，并使用`#define`指令来定义该宏的值。

请注意，如果您需要在C++程序中使用该变量，您需要在程序中包含`#ifdef`和`#ifndef`指令来检查该宏是否已定义，并使用`#define`指令来定义该宏的值。例如：
```c++
#include <iostream>

#ifdef MY_VARIABLE
#define MY_VARIABLE_VALUE MY_VARIABLE
#else
#define MY_VARIABLE_VALUE "default value"
#endif

int main() {

    std::cout << "MY_VARIABLE = " << MY_VARIABLE_VALUE << std::endl;

    return 0;

}
```
在这个例子中，我们使用`#ifdef`和`#ifndef`指令检查`MY_VARIABLE`宏是否已定义，并使用`#define`指令定义`MY_VARIABLE_VALUE`宏的值。如果`MY_VARIABLE`宏已定义，则将其值赋给`MY_VARIABLE_VALUE`宏；否则，将`"default value"`赋给`MY_VARIABLE_VALUE`宏。然后，我们在`main`函数中输出`MY_VARIABLE_VALUE`宏的值。

```c++
                            0  1  2  3  4  5  6  7  8  9
          elfin_base  0 |   -  0  1  1  1  0  0  0  1  1
 elfin_dummy_gripper  1 |   0  -  0  0  0  0  1  1  0  0
         elfin_link1  2 |   1  0  -  1  1  0  0  0  1  1
         elfin_link2  3 |   1  0  1  -  1  1  1  0  0  0
         elfin_link3  4 |   1  0  1  1  -  1  1  1  0  0
         elfin_link4  5 |   0  0  0  1  1  -  1  1  0  0
         elfin_link5  6 |   0  1  0  1  1  1  -  1  0  0
         elfin_link6  7 |   0  1  0  0  1  1  1  -  0  0
          screw_link  8 |   1  0  1  0  0  0  0  0  -  1
               world  9 |   1  0  1  0  0  0  0  0  1  -
                                       0  1  2  3  4  5  6  7  8  9
          elfin_base  0 |   -  0  1  1  1  0  0  0  1  1
 elfin_dummy_gripper  1 |   0  -  0  0  0  0  1  1  0  0
         elfin_link1  2 |   1  0  -  1  1  0  0  0  1  1
         elfin_link2  3 |   1  0  1  -  1  1  1  0  0  0
         elfin_link3  4 |   1  0  1  1  -  1  1  1  0  0
         elfin_link4  5 |   0  0  0  1  1  -  1  1  0  0
         elfin_link5  6 |   0  1  0  1  1  1  -  1  0  0
         elfin_link6  7 |   0  1  0  0  1  1  1  -  0  0
          screw_link  8 |   1  0  1  0  0  0  0  0  -  1
               world  9 |   1  0  1  0  0  0  0  0  1  -
```
