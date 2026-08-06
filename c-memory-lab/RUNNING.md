# C 实验启动与验证

这份文档只解决四件事：准备环境、运行单课、验证全部代码、判断结果是否正确。所有命令默认从 `c-memory-lab` 根目录执行。

## 1. 准备环境

macOS 安装 Xcode Command Line Tools：

```sh
xcode-select --install
```

确认工具可用：

```sh
cc --version
make --version
```

项目只依赖 C17 编译器和 `make`，不依赖 Keil、CubeMX 或开发板。macOS 的 `cc` 通常是 Apple Clang；Linux 上也可以使用 Clang 或 GCC。

先进入项目并查看命令：

```sh
cd /Users/derbysofti105/Documents/others/c-memory-lab
make help
```

## 2. 运行一节课

先查看可用课程：

```sh
make list
```

例如运行第 3 课：

```sh
make run LESSON=03_arrays
```

`LESSON` 填文件名去掉 `.c` 后的部分。命令执行过程是：

```text
lessons/03_arrays.c
        ↓ 编译
build/03_arrays
        ↓ 执行
终端输出
```

也可以拆开执行，以便看清编译和运行是两个步骤：

```sh
make build/03_arrays
./build/03_arrays
```

修改源文件后再次运行同一命令，`make` 会检测更新时间并重新编译。

## 3. 一节课怎样算验证完成

不要只以“程序没有报错”作为完成标准。每节课按以下顺序操作：

1. 阅读源码，但先不要运行。
2. 在 `WORKBOOK.md` 或 `EMBEDDED_WORKBOOK.md` 写下输出预测和内存图。
3. 使用 `make run LESSON=课程名` 编译运行。
4. 比较实际输出和预测，解释每个差异。
5. 完成源码末尾的 `TRY`，重新编译运行。
6. 不看原代码重写关键部分，再比较行为。

地址值每次运行都可能变化，这是操作系统地址随机化和运行环境造成的正常现象。应验证的是关系，而不是背某个地址：

- `p == &x` 是否成立；
- `&array[i + 1] - &array[i]` 是否跨过一个元素；
- `&p` 和 `p` 是否表示两个不同对象的位置；
- 修改 `*p` 后目标对象的值是否变化。

输出中的具体地址、`NULL` 显示形式以及部分类型大小可能因平台不同而不同。

## 4. 验证全部课程

普通编译和运行：

```sh
make clean all
make test
```

成功时最后显示：

```text
All lesson programs passed.
```

`make test` 为便于批量检查，会隐藏每节课的正常输出；想观察内容必须使用 `make run LESSON=...`。

## 5. 使用 Sanitizer 检查

UndefinedBehaviorSanitizer 用来发现部分未定义行为，例如有符号整数溢出和非法移位：

```sh
make sanitize
make test
```

AddressSanitizer 进一步检查越界访问、use-after-free 等内存错误：

```sh
make address-sanitize
make test
```

Sanitizer 不能证明程序绝对正确，它只能检查本次运行实际经过的路径。课程中的危险错误应放在独立最小程序中验证，不要写进正常课程再执行全量测试。

Sanitizer 构建后，恢复普通版本：

```sh
make clean all
```

## 6. 验证项目

```sh
make module-demo
make uart-core
make verify
```

`make verify` 包含 46 节课的普通编译和运行、多文件示例构建、UART 核心自动测试，但不包含 Sanitizer。日常修改后运行 `make verify`，阶段结束时再额外运行 Sanitizer。

## 7. 如何看待成功和失败

| 现象 | 含义 | 下一步 |
| --- | --- | --- |
| 编译器 warning/error | 类型、声明或语法可能有问题 | 从第一条诊断开始修复 |
| `make test` 中途停止 | 某个程序返回非 0 或异常退出 | 单独运行终止前显示的课程 |
| Sanitizer 报错 | 本次路径触发了内存或未定义行为 | 阅读第一处错误及对应源码行 |
| 输出地址与文档不同 | 通常正常 | 比较地址关系和步长 |
| UART 测试失败 | 协议、缓冲区或错误统计不符合断言 | 定位首个失败断言 |

排查时优先使用：

```sh
make clean
make run LESSON=课程名
```

如果仍无法理解，再记录源码行、完整编译诊断、实际输出、预期输出以及自己的内存图。

## 8. LLDB 观察内存

```sh
make build/04_stack
lldb ./build/04_stack
```

常用命令：

```text
b main                 在 main 设置断点
run                    启动程序
n                      执行下一行，不进入函数
s                      进入函数
p x                    打印表达式 x
p &x                   打印 x 的地址
frame variable         查看当前栈帧局部变量
memory read -c 16 &x   从 &x 开始查看 16 字节
bt                     查看调用栈
quit                   退出
```

调试器用于验证内存模型，不要一开始逐条汇编单步。先提出问题，例如“参数 `copy` 是否有独立地址”，再用断点和打印寻找证据。
