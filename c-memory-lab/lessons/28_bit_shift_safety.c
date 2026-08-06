#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t bit(unsigned int index)
{
    if (index >= 32U) {
        return 0U;
    }
    return UINT32_C(1) << index;
}

static uint32_t set_field(uint32_t value, uint32_t mask,
                          unsigned int shift, uint32_t field)
{
    if (shift >= 32U) {
        return value;
    }
    return (value & ~mask) | ((field << shift) & mask);
}

int main(void)
{
    uint32_t reg = 0U;
    reg |= bit(31U);
    reg = set_field(reg, UINT32_C(0x00000070), 4U, 5U);

    printf("CHAR_BIT=%d, reg=%#010x\n", CHAR_BIT, reg);
    printf("bit(32) guarded result=%#010x\n", bit(32U));

    /* TRY: 比较 1 << 31 与 UINT32_C(1) << 31 的类型和风险。 */
    return 0;
}
