# CubeMX 与 HAL 工作流

CubeMX 是配置和代码生成工具，不是理解硬件的替代品。官方文档说明它可以配置引脚、时钟及 GPIO、USART、SPI、I2C、定时器、ADC、DMA 等外设并生成初始化代码。

## 每次建工程的固定检查

1. 选对完整 MCU 型号和封装。
2. 配置 `SYS -> Debug = Serial Wire`，避免误关 SWD。
3. 根据板卡晶振配置 RCC，不能照抄其他板。
4. 在 Clock Configuration 检查红色冲突和各总线频率。
5. 为关键引脚设置 User Label。
6. 配置 NVIC 优先级和 DMA 请求。
7. 选择正确工具链和固件包版本。
8. 生成后先编译零业务代码，确认基线干净。

## 生成代码后要会追踪

以 GPIO 为例：

```text
main
  ↓
MX_GPIO_Init
  ↓
使能 GPIO 端口时钟
  ↓
构造 GPIO_InitTypeDef
  ↓
HAL_GPIO_Init
  ↓
配置模式、上下拉、速度和引脚
```

学习方法：

1. 从 `main.c` 找到 `MX_*_Init`；
2. 看句柄结构体和初始化参数；
3. 跳转到 HAL 实现；
4. 找到最终访问的寄存器字段；
5. 对照参考手册确认含义。

不用每次读完 HAL 全部源码，只追踪当前实验的一条关键路径。

## 用户代码放在哪里

CubeMX 生成文件中的自定义代码只能放在：

```c
/* USER CODE BEGIN ... */
/* USER CODE END ... */
```

更好的业务组织方式：

```text
Core/            CubeMX 生成的启动和初始化入口
Drivers/         CMSIS 与 HAL
App/             业务模块
Bsp/             板级 LED、按键、串口封装
Services/        协议、存储、日志、状态机
```

不要把所有业务都堆进 `while (1)`，也不要直接修改 HAL 库文件。

## HAL 三种常见调用模型

### 阻塞/轮询

```c
HAL_UART_Transmit(&huart1, data, length, timeout);
```

优点是简单；缺点是调用期间 CPU 可能等待。必须理解超时参数。

### 中断

```c
HAL_UART_Receive_IT(&huart1, buffer, length);
```

启动后立即返回，完成时进入中断并调用回调。回调中通常只更新状态、投递数据并重新启动接收。

### DMA

```c
HAL_UART_Receive_DMA(&huart1, buffer, length);
```

DMA 在外设和内存间搬运数据，CPU 处理完成/半完成事件。要保证缓冲区生命周期覆盖整个传输过程。

## 重新生成前后

每次改变 `.ioc`：

1. 提交或备份当前可运行版本；
2. 只在 User Code 区和独立模块写业务；
3. 生成后检查 diff；
4. 立即编译；
5. 做最小硬件回归测试；
6. 记录时钟、引脚和中断变化。

## 不要只保存 .ioc

团队工程至少版本控制：

- `.ioc`；
- 用户源码和头文件；
- 启动文件、链接配置；
- 工具链工程或 CMake 配置；
- 固件包/工具版本说明；
- 接线图和复现步骤。

生成文件是否全部提交由团队规范决定，但必须保证新成员可以稳定重建。
