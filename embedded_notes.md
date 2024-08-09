# 嵌入式学习手册

* 为什么.c里面的函数最好在.h中声明
  		* 头文件声明了，函数就不用管顺序

* 样例

  ```
  extern "C"
  {
  #include "im948_CMD.h"
  #include "motor_ctrl.h"
  
  }  
  ```

  

* ”<<“

		"<<" 运算符是C语言中的左移位运算符，它用于将一个数的各二进制位向左移动指定的位数，右侧空出的位用零填充。左移操作实际上是在原数的基础上乘以2的n次方，其中n是左移的位数。

语法如下：
```c
result = value << n;
```
其中，`value` 是要进行左移的数，`n` 是左移的位数，`result` 是左移后的结果。

具体例子：
```c
#include <stdio.h>

int main() {
    int num = 5; // 二进制表示为 0000 0101
    int result;

    result = num << 2; // 将 num 左移两位，等同于 num * (2^2)
    
    printf("Original number: %d\n", num);
    printf("Left shifted result: %d\n", result);

    return 0;
}
```

在这个例子中，`num` 的二进制表示为 `0000 0101`，将它左移两位，得到的结果是 `0001 0100`，对应的十进制值是 20。所以，`result` 的值将会是 20。左移操作将二进制数在二进制表示中向左移动了两位，并在右侧补充了两个零。





## 中断检测

为什么上升沿中断后可以检测到低电平？？？

确实能进入中断，但是为什么读到的电平都是低电平呢

## Timer



## 指针和取址

 符号 *p 代表这是一个指针类型，那是不是可以理解成 * 也是一种数据类型呢；然后想要取得一个数的地址需要用 & 符号对其进行取址，下面这个例子很好的说明了 指针和取址

如果你有一个函数 `void demo(uint8 * value);`，这个函数接受一个指向`uint8`（通常是`uint8_t`，表示8位无符号整数）的指针作为参数。这意味着你可以用它来传递单个`uint8_t`变量的地址，或者指向`uint8_t`数组的指针。

以下是如何使用这个函数的几个示例：

### 传递单个`uint8_t`变量的地址

```c
uint8_t single_value = 10;
demo(&single_value); // 正确：传递了single_value的地址
```

在这个例子中，`&single_value`是`single_value`变量的内存地址，它被传递给`demo`函数。

### 传递`uint8_t`数组的指针

```c
uint8_t array_values[5] = {10, 20, 30, 40, 50};
demo(array_values); // 正确：传递了数组的首地址
```

在这个例子中，`array_values`是数组的名称，它在函数调用中自动退化为指向数组首元素的指针。

### 使用指针变量

如果你有一个指向`uint8_t`的指针变量，你可以直接将它作为参数传递给`demo`函数：

```c
uint8_t *ptr = &single_value;
demo(ptr); // 正确：传递了指针变量ptr
```

在这个例子中，`ptr`是一个指向`uint8_t`的指针变量，它存储了`single_value`的地址。

### 函数的实际使用

下面是`demo`函数的一个可能实现，它简单地打印出它接收到的`uint8_t`值：

```c
#include <stdio.h>

void demo(uint8_t *value) {
    if (value != NULL) { // 检查指针是否非空
        printf("The value is: %u\n", *value);
    } else {
        printf("Pointer is NULL!\n");
    }
}

int main() {
    uint8_t single_value = 10;
    demo(&single_value); // 传递单个变量的地址

    uint8_t array_values[5] = {10, 20, 30, 40, 50};
    demo(array_values); // 传递数组的首地址

    uint8_t *ptr = &single_value;
    demo(ptr); // 传递指针变量

    return 0;
}
```

请注意，当传递数组的首地址时，`demo`函数只能访问数组的第一个元素，因为只有第一个元素的地址被提供。如果你需要访问整个数组，你需要传递指向数组每个元素的指针的数组，或者实现一个循环来遍历数组。



## if+end_if

`#if` 和 `#endif` 是C语言中预处理指令的一部分，它们用于条件编译。条件编译允许编译器根据特定的条件（通常是宏定义）来决定是否编译代码的某些部分。这是一种控制编译过程的强大机制，可以根据不同的编译环境或配置来包含或排除代码段。

以下是 `#if` 和 `#endif` 的基本用法和相关指令：

- `#if`：这个指令后面通常跟一个宏或者表达式。编译器会检查这个表达式的结果。如果结果为真（即非零或非空），则编译器会编译 `#if` 和 `#endif` 之间的代码直到遇到 `#endif`。如果结果为假，则跳过这段代码。

- `#ifdef`：这个指令后面跟一个宏的名称。如果该宏被定义了，则编译器会包含 `#ifdef` 和 `#endif` 之间的代码。

- `#ifndef`：与 `#ifdef` 相反，如果指定的宏没有被定义，编译器会包含 `#ifndef` 和 `#endif` 之间的代码。

- `#elif`：这个指令用于“或者”条件。它在 `#if` 或 `#elif` 表达式为假时提供另一种编译选项。

- `#else`：这个指令用于提供 `#if` 或 `#ifdef` 或 `#ifndef` 为假时的替代代码块。

- `#endif`：这个指令用来标记条件编译块的结束。

### 例子：

```c
#define MY_MACRO

#if defined(MY_MACRO)
    // 如果 MY_MACRO 被定义了，编译这段代码
    printf("MY_MACRO is defined.\n");
#elif defined(ANOTHER_MACRO)
    // 如果 MY_MACRO 没有定义，但 ANOTHER_MACRO 被定义了，编译这段代码
    printf("ANOTHER_MACRO is defined.\n");
#else
    // 如果两者都没有定义，编译这段代码
    printf("Neither macros are defined.\n");
#endif
```

在你提供的代码中，`#if CAN_RX0_INT_ENABLE` 检查宏 `CAN_RX0_INT_ENABLE` 是否被定义。如果该宏被定义，编译器将编译 `#if` 和 `#endif` 之间的代码，包括中断使能和ISR的定义。如果没有定义，那么这部分代码将不会被编译。

使用条件编译可以方便地在不同的项目或编译配置之间切换，而无需手动更改代码。



