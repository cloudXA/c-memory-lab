# 嵌入式工程化与入职规范

## 推荐分层

```text
Application
├── 状态机、业务规则、设备流程
Services
├── 协议、日志、参数存储、诊断
BSP/Drivers
├── LED、按键、传感器、通信设备封装
HAL/CMSIS
├── MCU 外设抽象和内核接口
Hardware
```

业务层不要直接散落 `HAL_GPIO_WritePin`、`HAL_UART_Transmit`。先封装板级接口：

```c
void bsp_led_set(bool on);
bool bsp_button_is_pressed(void);
```

这样换引脚、换板卡或做主机测试时，业务逻辑不用重写。

## 接口必须说明

每个公共函数至少明确：

- 参数是否允许 `NULL`；
- 缓冲区容量和实际长度；
- 单位：毫秒、赫兹、字节还是元素；
- 是否阻塞、最长多久；
- 可否从中断调用；
- 返回值和错误条件；
- 资源由谁拥有；
- 是否线程安全。

## 错误处理

不要丢弃 HAL 返回值：

```c
HAL_StatusTypeDef status = HAL_UART_Transmit(...);
if (status != HAL_OK) {
    /* 记录、重试、降级或进入故障状态。 */
}
```

区分错误类型：

- 参数错误：通常不应重试；
- 临时忙：可有限重试；
- 超时：记录上下文并恢复外设；
- 硬件缺失：降级或进入故障状态；
- 数据错误：丢帧并重新同步。

禁止无限重试和无超时等待。

## 状态机优于标志堆积

不要依赖多个互相矛盾的布尔值：

```c
bool initialized;
bool running;
bool error;
bool stopping;
```

使用有限状态：

```c
typedef enum {
    DEVICE_OFF,
    DEVICE_STARTING,
    DEVICE_RUNNING,
    DEVICE_ERROR
} device_state_t;
```

显式定义事件、合法迁移和超时。

## 时间处理

避免阻塞式业务：

```c
HAL_Delay(1000);
```

在简单主循环中使用非阻塞时间差：

```c
uint32_t now = HAL_GetTick();
if ((uint32_t)(now - last) >= period_ms) {
    last = now;
    do_periodic_work();
}
```

使用无符号差值可自然处理计数回绕，但周期必须小于可区分范围。

## 全局变量与共享数据

- 模块内部状态使用文件作用域 `static` 隐藏；
- 通过函数接口访问，不暴露可写全局变量；
- ISR 与主循环共享数据时，只加 `volatile` 不一定够；
- 多字节读写、读改写操作可能需要临界区或原子机制；
- RTOS 下用队列、通知或互斥锁表达通信。

## 内存策略

- 明确 Flash、静态 RAM、栈和堆预算；
- 大缓冲区避免放在小任务栈上；
- 动态分配只在所有权和失败路径清晰时使用；
- 长期运行系统关注碎片；
- FreeRTOS 任务创建和队列也会消耗 RAM；
- 查看 map 文件和任务栈高水位，不凭感觉估算。

## 日志

日志至少包含模块、级别和关键状态：

```text
[I][sensor] initialized
[W][uart] rx overflow dropped=12
[E][i2c] timeout addr=0x44 state=READ
```

生产代码需要：

- 编译期开关和日志级别；
- 避免 ISR 中阻塞打印；
- 避免打印敏感信息；
- 高频路径使用计数器或缓冲日志。

## Git 与可复现构建

每个可运行节点提交一次：

```text
feat(gpio): add active-low LED control
feat(uart): receive commands with ring buffer
fix(i2c): recover bus after timeout
```

README 记录：硬件版本、接线、工具版本、固件包版本、构建下载方法和已知问题。

## 测试策略

- 纯 C 模块在 Mac/Linux 主机上单元测试；
- HAL 通过接口封装后使用 fake/mock；
- 板上测试验证真实外设；
- 故障注入：拔掉传感器、制造校验错误、填满缓冲区、延迟响应；
- 回归测试覆盖启动、通信、错误恢复和长时间运行。

## 代码审查清单

- 数组长度是否来自真实容量；
- `snprintf` 是否检查截断；
- 超时单位是否正确；
- 中断回调是否快速；
- DMA 缓冲区生命周期是否足够；
- 标志是否存在竞态；
- HAL 返回值是否处理；
- 重新生成 CubeMX 是否覆盖业务代码；
- 是否存在魔法数字和硬编码引脚；
- 失败路径是否释放/恢复资源。
