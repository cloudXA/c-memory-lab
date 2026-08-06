#include <stdint.h>
#include <stdio.h>

#define CONTROL_ENABLE (UINT32_C(1) << 0U)
#define CONTROL_MODE_MASK (UINT32_C(3) << 4U)
#define STATUS_RX_READY (UINT32_C(1) << 0U)
#define STATUS_ERROR (UINT32_C(1) << 1U)

struct SimulatedPeripheral {
    volatile uint32_t control;
    volatile uint32_t status;
};

static void set_mode(struct SimulatedPeripheral *device, uint32_t mode)
{
    uint32_t value = device->control;
    value &= ~CONTROL_MODE_MASK;
    value |= (mode << 4U) & CONTROL_MODE_MASK;
    device->control = value;
}

static void write_one_to_clear(struct SimulatedPeripheral *device, uint32_t mask)
{
    /* 真实 W1C 寄存器写 1 清位；这里用软件模拟它的最终效果。 */
    device->status &= ~mask;
}

int main(void)
{
    struct SimulatedPeripheral device = {
        .control = 0U,
        .status = STATUS_RX_READY | STATUS_ERROR
    };

    device.control |= CONTROL_ENABLE;
    set_mode(&device, 2U);
    printf("control=%#010x\n", device.control);

    write_one_to_clear(&device, STATUS_ERROR);
    printf("status after clear error=%#010x\n", device.status);

    /* TRY: 解释为什么真实 W1C 状态寄存器不能照搬普通 REG |= mask。 */
    return 0;
}
