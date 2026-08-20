#include <stdint.h>
#include <stdio.h>

#define STATUS_READY (UINT32_C(1) << 0U)
#define CONTROL_ENABLE (UINT32_C(1) << 3U)

struct PeripheralRegisters {
    volatile uint32_t status;
    volatile uint32_t control;
    volatile uint32_t data;
};

static void peripheral_enable(struct PeripheralRegisters *registers)
{
    registers->control |= CONTROL_ENABLE;
}

int main(void)
{
    struct PeripheralRegisters simulated = {0};

    peripheral_enable(&simulated);
    simulated.status |= STATUS_READY; /* 模拟硬件改变状态。 */
    simulated.data = UINT32_C(1234);

    if ((simulated.status & STATUS_READY) != 0U) {
        printf("data=%u, control=%#x\n", simulated.data, simulated.control);
    }

    /* TRY: 解释 volatile 为何不提供原子性、互斥或线程安全。 */
    return 0;
}
// data=1234, control=0x8