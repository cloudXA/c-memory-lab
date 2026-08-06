#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MCU_SRAM_BYTES (20U * 1024U)

struct MemoryBudget {
    size_t static_data;
    size_t main_stack;
    size_t rtos_heap;
    size_t task_stacks;
    size_t safety_margin;
};

static size_t total(const struct MemoryBudget *budget)
{
    return budget->static_data + budget->main_stack + budget->rtos_heap +
           budget->task_stacks + budget->safety_margin;
}

int main(void)
{
    const struct MemoryBudget budget = {
        .static_data = 4096U,
        .main_stack = 1024U,
        .rtos_heap = 4096U,
        .task_stacks = 6144U,
        .safety_margin = 2048U
    };
    size_t used = total(&budget);

    printf("budget=%zu / %u bytes, remaining=%zu\n",
           used, MCU_SRAM_BYTES,
           used <= MCU_SRAM_BYTES ? MCU_SRAM_BYTES - used : 0U);

    /* TRY: 从真实 STM32 map 文件提取静态 RAM，并加入任务栈实测。 */
    return used <= MCU_SRAM_BYTES ? 0 : 1;
}
