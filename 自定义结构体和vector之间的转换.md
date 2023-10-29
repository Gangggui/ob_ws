
```c++
#include <iostream>
#include <vector>

using namespace std;

// 定义一个自定义结构体
struct vec2 {
    float x;
    float y;
    
    vec2(float _x, float _y) : x(_x), y(_y) {}
};

// 定义模板转换函数，将vector中的元素转换成vec2类型的对象
template <typename T>
vec2 toVec2(const T& v) {
    return vec2(static_cast<float>(v[0]), static_cast<float>(v[1]));
}

int main() {
    // 创建一个vector对象
    vector<int> v = {1, 2};
    
    // 调用模板转换函数，将vector中的元素转换成vec2类型的对象
    vec2 v2 = toVec2(v);
    
    // 输出转换后的结果
    cout << "v2.x = " << v2.x << ", v2.y = " << v2.y << endl;
    
    return 0;
}
```