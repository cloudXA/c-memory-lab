# 上官二号开发板档案

这份文件必须根据你手上的实物、原理图和 CubeMX 工程填写。不要只依赖课程口述。

## 已知与待确认

| 项目 | 当前记录 |
|---|---|
| 开发板名称 | 上官二号 |
| MCU | `STM32F103C8T6`（公开课程资料常见配置，待实物确认） |
| CPU 内核 | Cortex-M3（若 MCU 确认为 STM32F103C8T6） |
| 调试接口 | SWD，待确认 ST-LINK 型号和接线 |
| 系统时钟 | 待从 CubeMX Clock Configuration 确认 |
| 外部高速晶振 HSE | 待从原理图/板上晶振丝印确认 |
| 外部低速晶振 LSE | 待确认 |
| 用户 LED | 待确认引脚及高/低电平点亮方式 |
| 用户按键 | 待确认引脚、上下拉和有效电平 |
| 串口 | 待确认 USART 编号、TX/RX 引脚和 USB-TTL 电平 |

## 实物核对步骤

1. 拍下 MCU 顶部丝印，记录完整型号。
2. 在 CubeMX 的 MCU Selector 中确认 Part Number。
3. 找到课程提供的原理图，标记 LED、按键、晶振、串口和 SWD。
4. 确认板上供电是 3.3 V 还是包含 5 V 转换，不要假设 GPIO 可承受 5 V。
5. 确认 ST-LINK 的 `SWDIO/SWCLK/GND/3V3` 连接。

## 引脚表

| 功能 | MCU 引脚 | CubeMX 标签 | 电气特性 | 备注 |
|---|---|---|---|---|
| LED | 待填 | `LED` | 高/低有效待填 | |
| KEY | 待填 | `KEY` | 上拉/下拉待填 | |
| USART TX | 待填 | `UART_TX` | 3.3 V TTL | |
| USART RX | 待填 | `UART_RX` | 3.3 V TTL | |
| I2C SCL | 待填 | `I2C_SCL` | 通常需要上拉 | |
| I2C SDA | 待填 | `I2C_SDA` | 通常需要上拉 | |

## 时钟档案

完成时钟实验后填写：

```text
时钟源：
HSE 频率：
PLL 倍频：
SYSCLK：
HCLK：
PCLK1：
PCLK2：
APB1 定时器时钟：
APB2 定时器时钟：
SysTick 频率：
```

## 芯片资源核对

从数据手册而不是营销页面填写：

```text
Flash：
SRAM：
GPIO 数量：
通用定时器：
高级定时器：
USART：
I2C：
SPI：
ADC：
DMA 通道：
工作电压：
最高主频：
```
