# UART Device Core

一个不依赖 STM32 HAL 的纯 C UART 协议核心，可在 Mac/Linux 上测试，再移植到 STM32。

## 协议

```text
0xAA | payload_length | command | payload... | checksum
```

校验和为 `payload_length + command + payload` 的低 8 位。

## 架构

```text
UART ISR/DMA
  ↓ uart_device_feed_byte / uart_device_feed
环形缓冲区
  ↓ uart_device_process（主循环或通信任务）
流式解析器
  ↓
command_handler
```

输入函数不执行命令处理。STM32 中断只投递字节，主循环或 FreeRTOS 通信任务调用 `uart_device_process`。

## 运行

```sh
make clean test
```

## STM32 移植

1. 将 `include/uart_device.h` 和 `src/uart_device.c` 加入工程。
2. 初始化一个静态 `struct UartDevice`，确保生命周期覆盖所有中断/DMA。
3. 在 UART 回调中调用输入函数。
4. 在主循环或通信任务调用 `uart_device_process`。
5. 命令回调只依赖 BSP/业务接口，不直接散落 HAL 调用。

## 设计约束

- 不使用动态内存；
- 所有容量固定且检查边界；
- 错误帧后可重新同步；
- 环形缓冲区满时拒绝新字节并统计；
- 校验和用于教学，不适合高可靠/安全协议；
- ISR/任务间真正并发时，索引可见性和原子性必须根据 MCU/RTOS 添加临界区或适当同步。
