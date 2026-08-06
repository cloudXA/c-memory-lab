#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define DMA_CAPACITY 16U

static uint8_t dma_buffer[DMA_CAPACITY];
static bool dma_active;

static bool dma_start(uint8_t *buffer, size_t capacity)
{
    if (buffer == NULL || capacity == 0U || dma_active) {
        return false;
    }
    dma_active = true;
    return true;
}

static void simulated_dma_complete(void)
{
    for (size_t i = 0; i < DMA_CAPACITY; ++i) {
        dma_buffer[i] = (uint8_t)i;
    }
    dma_active = false;
}

int main(void)
{
    if (!dma_start(dma_buffer, sizeof dma_buffer)) {
        return 1;
    }
    simulated_dma_complete();
    printf("DMA complete, first=%u last=%u\n",
           (unsigned int)dma_buffer[0],
           (unsigned int)dma_buffer[DMA_CAPACITY - 1U]);

    /* TRY: 解释为什么函数内局部数组不能在函数返回后继续交给 DMA。 */
    return 0;
}
