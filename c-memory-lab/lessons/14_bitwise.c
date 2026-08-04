#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (UINT32_C(1) << (n))

int main(void)
{
    uint32_t reg = 0U;

    reg |= BIT(3);
    reg |= BIT(5);
    printf("置位 3、5 后: %#010x\n", reg);

    reg &= ~BIT(3);
    printf("清除第 3 位: %#010x\n", reg);

    reg ^= BIT(5);
    printf("翻转第 5 位: %#010x\n", reg);

    bool bit_five_is_set = (reg & BIT(5)) != 0U;
    printf("第 5 位是否为 1: %s\n", bit_five_is_set ? "yes" : "no");

    /* TRY: 用掩码写一个 set_field(value, mask, shift, field) 函数。 */
    return 0;
}
