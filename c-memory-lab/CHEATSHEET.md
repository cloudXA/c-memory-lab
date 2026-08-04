# C 速查表

## 声明阅读

从变量名向外读：

```c
int *p;                 // p 是指向 int 的指针
const int *p;           // p 指向只读 int
int *const p = &x;      // p 本身不能改指向
int **pp;               // pp 指向一个 int * 对象
int (*handler)(int);    // handler 是函数指针
```

## 内存分配

```c
int *p = malloc(count * sizeof(*p));
if (p == NULL) {
    /* 处理失败 */
}
free(p);
p = NULL;
```

## 位操作

```c
#define BIT(n) (UINT32_C(1) << (n))

value |= BIT(3);         // 置位
value &= ~BIT(3);        // 清零
value ^= BIT(3);         // 翻转
bool set = (value & BIT(3)) != 0U;
```

## 安全字符串

```c
char buffer[32];
int written = snprintf(buffer, sizeof buffer, "%s:%d", name, value);
if (written < 0 || (size_t)written >= sizeof buffer) {
    /* 编码失败或被截断 */
}
```

## 头文件模板

```c
#ifndef MODULE_H
#define MODULE_H

#include <stddef.h>

int module_do_work(const char *input, size_t length);

#endif
```

## 常用编译选项

```sh
cc -std=c17 -Wall -Wextra -Wpedantic -Wconversion -g -O0 main.c
```
