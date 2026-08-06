# STM32 嵌入式入职学习路线

本项目与 `c-memory-lab` 平级，配合“上官二号”STM32 课程使用。线上课程负责带你用 STM32CubeMX 配置工程并完成实验，本项目负责补齐：

- 为什么这样配置；
- HAL 最终控制了什么硬件；
- 遇到异常如何定位；
- 企业项目如何组织；
- 面试和入职要求掌握什么。

## 当前假设

公开课程资料显示“上官二号”常用 `STM32F103C8T6`。请先查看芯片丝印和 CubeMX 工程中的 Part Number，在 [BOARD_PROFILE.md](BOARD_PROFILE.md) 填写确认结果。如果型号不同，以实际芯片的数据手册和参考手册为准。

## 学习主线

```text
c-memory-lab
    ↓
开发环境、下载与调试
    ↓
Cortex-M3、存储器映射、启动流程
    ↓
时钟树、GPIO、EXTI
    ↓
定时器、PWM、输入捕获
    ↓
UART、I2C、SPI、ADC
    ↓
中断、DMA、环形缓冲区
    ↓
看门狗、Flash、低功耗
    ↓
FreeRTOS
    ↓
工程化综合项目与求职准备
```

## 每个实验的四层完成标准

不要只记录“CubeMX 选了哪个下拉框”。每个实验必须能回答：

1. **现象层**：输入、输出和验收现象是什么？
2. **API 层**：调用了哪些 HAL API，参数和返回值是什么？
3. **硬件层**：涉及哪些时钟、引脚、寄存器位、中断或 DMA 请求？
4. **工程层**：超时、错误、并发、资源生命周期和日志如何处理？

## 资料导航

- [BOARD_PROFILE.md](BOARD_PROFILE.md)：开发板、芯片和调试器档案
- [ROADMAP.md](ROADMAP.md)：8 周学习安排
- [FOUNDATIONS.md](FOUNDATIONS.md)：Cortex-M、启动、内存和时钟基础
- [PERIPHERALS.md](PERIPHERALS.md)：各外设的原理、实验与排错
- [CUBEMX_WORKFLOW.md](CUBEMX_WORKFLOW.md)：CubeMX/HAL 的正确使用方式
- [DEBUGGING.md](DEBUGGING.md)：烧录、断点、HardFault 和波形排查
- [ENGINEERING.md](ENGINEERING.md)：目录、接口、状态机、错误处理和测试
- [RTOS.md](RTOS.md)：FreeRTOS 入门与并发模型
- [PROJECTS.md](PROJECTS.md)：三个阶段项目
- [LAB_TEMPLATE.md](LAB_TEMPLATE.md)：每次实验的记录模板
- [WORKBOOK.md](WORKBOOK.md)：原理自测题
- [INTERVIEW.md](INTERVIEW.md)：面试与入职检查
- [REFERENCES.md](REFERENCES.md)：官方资料阅读顺序

## 学习纪律

- CubeMX 生成的代码能运行，不代表你理解了外设。
- 不要求背寄存器地址，但要会从参考手册找到寄存器和位。
- 不要求背 HAL API，但要知道参数、返回值、阻塞性和超时。
- 每个模块至少做一次“修改参数并预测结果”和一次“故意制造故障”。
- 所有业务代码放在可维护区域或独立模块，避免重新生成时丢失。
- 每周至少一次脱离视频，独立重建最小工程。

## 与 C 课程的关系

遇到以下问题时回到 `../c-memory-lab`：

| STM32 场景 | 对应 C 知识 |
|---|---|
| HAL 句柄与回调 | 结构体、指针、函数指针 |
| UART 接收缓存 | 数组、指针、环形缓冲区 |
| 寄存器操作 | 定宽整数、位运算、`volatile` |
| 中断共享标志 | 生命周期、`volatile`、并发 |
| DMA 缓冲区 | 数组边界、对象生命周期 |
| 动态对象 | 堆、所有权、错误处理 |

## 先做什么

1. 填写 [BOARD_PROFILE.md](BOARD_PROFILE.md)。
2. 阅读 [FOUNDATIONS.md](FOUNDATIONS.md) 的 1～4 节。
3. 用 [LAB_TEMPLATE.md](LAB_TEMPLATE.md) 记录当前 GPIO 实验。
4. 按 [ROADMAP.md](ROADMAP.md) 推进，不需要等 C 全部学完。
