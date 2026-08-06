# 官方资料阅读顺序

优先使用与你实际 MCU 完整型号匹配的 ST 官方资料。

## 板卡确认后下载

1. MCU Datasheet：引脚、电气参数、封装、Flash/RAM。
2. Reference Manual：RCC、GPIO、TIM、USART、I2C、SPI、ADC、DMA 等。
3. Cortex-M Programming Manual：内核、异常、NVIC。
4. Errata Sheet：芯片勘误和规避方法。
5. 开发板原理图：LED、按键、晶振、供电和接口。

## 官方在线资料

- STM32CubeMX 产品页：<https://www.st.com/en/development-tools/stm32cubemx.html>
- STM32CubeMX 文档：<https://dev.st.com/stm32cube-docs/stm32cubemx/>
- STM32F1 产品入口：<https://www.st.com/en/microcontrollers-microprocessors/stm32f1-series.html>
- FreeRTOS 文档：<https://www.freertos.org/Documentation/RTOS_book.html>
- ARM Cortex-M3 文档入口：<https://developer.arm.com/Processors/Cortex-M3>

## 手册阅读方法

不要从第一页顺序读到最后。做 UART 实验时：

```text
数据手册：确认 USART 引脚复用和电气条件
参考手册：读 USART 功能说明、波特率、状态标志和中断
HAL 头文件：读 API 参数、返回值和调用模式
原理图：确认开发板连接
勘误表：搜索 USART/UART 相关问题
```

每次实验记录实际阅读的章节号和结论。

## 关于“上官二号”型号

公开学习资料中可见该板常与 `STM32F103C8T6` 一起使用，但这不是芯片厂商的官方板卡型号。最终依据必须是你手上芯片丝印、课程原理图和 CubeMX 工程 Part Number。
