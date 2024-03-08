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



## Timer

