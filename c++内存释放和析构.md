![[Pasted image 20230906191501.png]]

系统：**Linux x86_64**

##### 相同变量类型，先声明的后析构
同类型变量（此处类型为：全局变量、局部变量、静态变量）下，先声明定义的后释放内存
```c++
#include <iostream>  
  
#define BACKWARD_HAS_DW 1  
#include "backward.hpp"  
namespace backward{  
    backward::SignalHandling sh;  
}  
  
#include <iostream>  
using namespace std;  
  
class A{  
public:  
    explicit A(int data) : i(data) {  
        cout << "A申请内存" << i << endl;  
    }  
    ~A(){  
        cout << "A释放内存" << i << endl;  
    }  
private:  
    int i=0;  
};  
class B{  
public:  
    explicit B(int data) : i(data) {  
        cout << "B申请内存" << i << endl;  
    }  
    ~B(){  
        cout << "B释放内存" << i << endl;  
    }  
private:  
    int i=0;  
};  
class C{  
public:  
    explicit C(int data) : i(data) {  
        cout << "C申请内存" << i << endl;  
    }  
    ~C(){  
        cout << "C释放内存" << i << endl;  
    }  
private:  
    int i=0;  
};  
class D{  
public:  
    explicit D(int data) : i(data) {  
        cout << "D申请内存" << i << endl;  
    }  
    ~D(){  
        cout << "D释放内存" << i << endl;  
    }  
private:  
    int i=0;  
};  
  
class All {  
private:  
    C c = C(22);  
    D d = D(22);  
    static A aa; ;  
};  
A All::aa = A(22);  
  
//主函数具体代码如下：  
C c(1);  
static A a1(1);  
D d(2);  
int main()  
{  
    All all;  
    static A a(3);  
    B b(4);  
    static C c(5);  
    A a2(2);  
    return 0;  
}
```
![[Pasted image 20230906193840.png]]
###### 不同变量类型，释放顺序与位置无关，与变量类型有关。
 普通局部变量>静态局部变量>全局变量

###### 由用户申请的堆内存，在用户手动释放的时候释放，若没有释放，会造成内存泄漏。

###### Q: 类对象的构造和析构顺序
1. 调用父类的构造函数
2. 调用成员变量的构造函数(调用顺序与声明顺序相同);
3. 调用自身的构造函数
 析构与构造顺序相反

构造：类内静态成员 > 全局变量 > 局部变量(不区分静态与否，声明顺序)
析构：局部变量 > 局部静态变量 > 全局变量 > 类内静态成员
###### Q: Map/Vector里包含自定义类型时，析构顺序
###### Q: 自定义类型析构顺序
