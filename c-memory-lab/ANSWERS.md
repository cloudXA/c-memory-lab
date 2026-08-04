# 逐课参考答案

先独立完成实验再看答案。地址和部分类型大小依赖平台，重点看关系。

## 01 字节与变量

- `sizeof(char)` 必为 1；本机通常 `int` 为 4、`double` 为 8 字节，以输出为准。
- Apple Silicon 是小端机器，`0x12345678` 通常显示为 `78 56 34 12`。
- 内存只保存位，类型决定读取字节数和解释方式。
- `TRY`：小端下 `1`、`256`、`-1` 常见字节分别为 `01 00 00 00`、`00 01 00 00`、`ff ff ff ff`。

## 02 一级指针

- `p` 是 `x` 的地址；`&p` 是指针对象自己的地址；`*p` 是通过地址访问 `x`。
- `*p = 99` 修改 `x`，不改变 `p` 的地址值。
- `int` 决定解引用的访问方式，也决定 `p + 1` 的步长。

```c
int y = 7;
p = &y;
*p = 88; /* y 变成 88。 */
```

## 03 数组

- 相邻元素地址相差 `sizeof(int)`。
- `values` 转换后的地址与 `&values[0]` 相同，但数组和指针类型不同，`sizeof` 结果也不同。
- `values + 2` 指向第三个元素，因此 `*(values + 2) == values[2]`。

```c
for (int *p = values; p < values + 4; ++p) {
    printf("%d\n", *p);
}
```

## 04 栈与函数

- `change_value` 得到整数副本，修改副本不影响 `x`。
- `change_through_pointer` 得到地址副本，`*address` 仍能访问 `x`。
- 函数返回后局部自动对象生命周期结束，指向它的指针会悬空。

```text
address 对象 ──保存地址──> main 中的 x 对象
```

## 05 堆

- `p` 通常是栈上的局部对象，`p` 指向的是动态存储。
- `free(p)` 结束动态存储的生命周期，不销毁 `p`。
- `p = NULL` 只修改 `p`，其他别名仍保存失效地址。

```c
int *alias = p;
free(p);
p = NULL;
/* alias 是悬空指针，不能解引用。 */
alias = NULL;
```

## 06 结构体

- 总大小可能大于字段大小之和，因为存在对齐填充。
- 本机常见偏移是 `tag=0`、`count=4`、`state=8`，总大小 12，以实际输出为准。
- 将两个 `char` 相邻排列通常可减少填充。

```c
struct Sample { char tag; char state; int count; };
```

## 07 二级指针

- `pp` 是变量名，类型为 `int **`，保存 `p` 的地址。
- `*pp` 访问 `p`，`**pp` 再访问 `p` 指向的整数。
- 函数要修改调用者的 `int *` 对象，就要接收它的地址 `int **`。

```text
out ──> heap_number ──> 堆上的 int
```

## 08 控制流

- `for (初始化; 条件; 更新)` 中，初始化执行一次，每轮前判断条件，每轮后更新。
- `switch` 适合离散整数或枚举状态。

```c
switch (state) {
case 0: puts("off"); break;
case 1: puts("running"); break;
case 2: puts("error"); break;
default: puts("unknown"); break;
}
```

## 09 整数类型

- `uint8_t` 参与算术时通常提升为 `int`，所以 255 加 1 可得到 256。
- `-1` 转 `unsigned int` 后通常为 `UINT_MAX`，因此不小于 `1U`。
- 宽类型转窄类型可能截断，有符号和无符号混用应显式设计。

`TRY`：加入 `uint8_t narrowed = large;`，保留 `-Wconversion` 阅读警告，然后删除危险代码。

## 10 作用域与 static

- 作用域决定名字在哪里可见，存储期决定对象活多久。
- 局部 `static` 只有块作用域，但对象存活到程序结束且只初始化一次。
- 文件作用域 `static` 具有内部链接，仅当前 `.c` 可见。

## 11 字符串

- `sizeof(array)` 是数组总容量，包含末尾 `\0`；`strlen` 不包含 `\0`。
- 字符串字面量不可修改，应用 `const char *` 接收。

```c
char destination[6];
int n = snprintf(destination, sizeof destination, "%s-%d", editable, 7);
if (n < 0 || (size_t)n >= sizeof destination) puts("truncated");
```

## 12 const 指针

- `const int *p`：能改指向，不能通过 `p` 修改目标。
- `int *const p`：不能改指向，能修改目标。
- `const int *const p`：两者都受限。
- `TRY` 中两个非法赋值都会被编译器拒绝。

## 13 枚举与联合体

- 枚举为有限状态提供名字；联合体成员从同一地址开始、共享同一存储。

```c
static const char *state_name(enum DeviceState state)
{
    switch (state) {
    case DEVICE_OFF: return "off";
    case DEVICE_RUNNING: return "running";
    case DEVICE_ERROR: return "error";
    }
    return "invalid";
}
```

## 14 位运算

```c
value |= BIT(n);          /* 置位 */
value &= ~BIT(n);         /* 清零 */
value ^= BIT(n);          /* 翻转 */
(value & BIT(n)) != 0U;   /* 测试 */
```

```c
static uint32_t set_field(uint32_t value, uint32_t mask,
                          unsigned int shift, uint32_t field)
{
    return (value & ~mask) | ((field << shift) & mask);
}
```

## 15 函数指针与回调

- 回调把行为传入通用代码，`void *context` 携带调用者状态；真实类型和生命周期必须正确。

```c
static void print_above(int value, void *context)
{
    const int *threshold = context;
    if (value > *threshold) printf("%d\n", value);
}
```

## 16 预处理器

- 宏是文本替换，没有类型检查，参数可能被重复求值。
- `SQUARE_BAD(1 + 2)` 展开后不是预期的 9。

```sh
cc -E lessons/16_preprocessor.c | less
cc -DDEBUG lessons/16_preprocessor.c -o build/16_debug
```

## 17 声明、定义与链接

- 声明提供名字和类型，定义提供函数实体或对象存储。
- 头文件放公共声明，`.c` 放定义；文件作用域 `static` 隐藏模块实现。

```sh
cc -c examples/multi_file/counter.c -o counter.o
cc -c examples/multi_file/main.c -o main.o
cc counter.o main.o -o app
```

也可执行 `make module-demo`。

## 18 错误处理

- 返回码表达成功或失败，输出参数携带结果。
- 失败时输出可能未写入，所以必须先检查状态。

```c
status = average(NULL, 3U, &result); /* INVALID_ARGUMENT */
status = average(values, 0U, &result); /* EMPTY */
```

## 19 所有权

- 直接复制 `Message` 只复制指针，是浅拷贝；可能导致悬空指针或重复释放。
- 应禁止复制、实现深拷贝或明确转移所有权。

```c
struct Message copy = {0};
if (message_init(&copy, message.text)) {
    message_destroy(&copy);
}
```

## 20 环形缓冲区

- `head` 是下次写入位置，`tail` 是下次读取位置，`count` 是元素数。
- `count == 0` 为空，`count == capacity` 为满，取模使索引绕回。

```c
ring_push(&buffer, 1U); ring_push(&buffer, 2U);
ring_pop(&buffer, &value);
ring_push(&buffer, 3U); ring_push(&buffer, 4U);
ring_pop(&buffer, &value);
ring_push(&buffer, 5U); /* head/tail 会绕回。 */
```

## 21 状态机

- 不接受的事件可以保持原状态或返回错误，但规则必须明确。
- 状态机集中描述合法迁移，避免多个布尔值形成非法组合。

```text
OFF + POWER_ON -> STARTING
STARTING + READY -> RUNNING
RUNNING + POWER_OFF -> STOPPING
STOPPING + READY -> OFF
任意运行态 + FAILURE -> ERROR
ERROR + RESET -> OFF
```

## 22 字节序

- 协议字节序不能依赖 CPU；逐字节移位可同时避免字节序、对齐和别名问题。

```c
static void encode_u32_be(uint32_t v, uint8_t out[4])
{
    out[0] = (uint8_t)(v >> 24U); out[1] = (uint8_t)(v >> 16U);
    out[2] = (uint8_t)(v >> 8U);  out[3] = (uint8_t)v;
}

static uint32_t decode_u32_be(const uint8_t in[4])
{
    return ((uint32_t)in[0] << 24U) | ((uint32_t)in[1] << 16U) |
           ((uint32_t)in[2] << 8U) | (uint32_t)in[3];
}
```

## 23 volatile

- `volatile` 要求每次都实际访问对象，适用于硬件寄存器或中断改变的标志。
- 它不提供原子性、互斥、线程安全或完整的内存顺序。
- 即便 `counter` 是 `volatile`，`counter++` 仍可能由读、改、写三步组成。

## 24 驱动接口

- 业务层依赖接口，不依赖具体硬件，因此可以替换真实驱动和模拟驱动。

```c
struct ConstantData { float value; };

static bool constant_read(struct Sensor *sensor, float *out)
{
    const struct ConstantData *data = sensor->context;
    if (out == NULL) return false;
    *out = data->value;
    return true;
}
```

## 最终口述题

```c
int *p = malloc(10 * sizeof(*p));
```

- `p` 是 `int *` 指针对象；`*p` 的表达式类型为 `int`。
- 普通情况下 `sizeof` 不执行解引用，只取得类型大小。
- `malloc` 请求足以容纳 10 个 `int` 的动态存储，失败返回空指针。
- `p + 1` 前进 `sizeof(int)` 字节；成功后写入后才能读取 `p[0]`～`p[9]`。
- `free(p)` 后动态存储失效，`p` 自身仍存在但成为悬空指针，通常随后设为 `NULL`。
