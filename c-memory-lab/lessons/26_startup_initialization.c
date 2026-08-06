#include <stdio.h>

static int copied_from_image = 123;
static int cleared_before_main;

int main(void)
{
    printf("进入 main 时：initialized=%d, zero=%d\n",
           copied_from_image, cleared_before_main);

    /*
     * STM32 启动代码通常在 main 前把 .data 初值从 Flash 复制到 SRAM，
     * 并把 .bss 清零。主机系统由加载器和 C 运行时完成对应工作。
     */
    /* TRY: 找到 STM32 工程的 Reset_Handler、.data 和 .bss 初始化循环。 */
    return 0;
}
