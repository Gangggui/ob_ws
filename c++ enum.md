
1. 枚举类型在内存中被视为整数类型，因此在使用memcpy时，会将枚举类型的值作为整数进行复制。而在使用sizeof时，会返回枚举类型的大小，即通常为4字节的整数类型大小。

2. 由于枚举类型是一种离散的类型，不能直接使用memcpy进行赋值操作。如果想要复制一个枚举变量，可以将其转换为一个整数类型，然后再进行复制操作。例如：

```c++
#include <iostream>
#include <cstring>
#include "Better_enum.h"

int main() {
    Better_enum e1 = Better_enum::Value1;
    Better_enum e2;

    std::memcpy(&e2, &e1, sizeof(e1)); // 错误的复制方式
    std::cout << "e1 = " << static_cast<int>(e1) << std::endl;
    std::cout << "e2 = " << static_cast<int>(e2) << std::endl;

    int value = static_cast<int>(e1);
    std::memcpy(&e2, &value, sizeof(value)); // 正确的复制方式
    std::cout << "e1 = " << static_cast<int>(e1) << std::endl;
    std::cout << "e2 = " << static_cast<int>(e2) << std::endl;

    return 0;
}
```

在上面的例子中，我们首先尝试使用memcpy直接复制枚举变量e1到e2，这是错误的方式，因为枚举类型是离散的类型，不能直接进行内存复制。然后我们将e1转换为整数类型value，再使用memcpy将value复制到e2中，这样就能正确地复制枚举变量了。注意，这种方式只适用于枚举类型的变量，对于包含指针或其他非平凡类型的变量，需要使用更加复杂的复制方式。


### Better_enum库
