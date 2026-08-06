#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BLOCK_SIZE 4U

struct DmaHandoff {
    uint8_t blocks[2][BLOCK_SIZE];
    size_t ready_length[2];
    bool ready[2];
    size_t dma_index;
};

static void simulated_dma_complete(struct DmaHandoff *handoff, size_t length)
{
    size_t completed = handoff->dma_index;
    handoff->ready_length[completed] = length;
    handoff->ready[completed] = true;
    handoff->dma_index ^= 1U;
}

static void process_ready(struct DmaHandoff *handoff)
{
    for (size_t block = 0; block < 2U; ++block) {
        if (!handoff->ready[block]) continue;
        printf("block %zu:", block);
        for (size_t i = 0; i < handoff->ready_length[block]; ++i)
            printf(" %u", (unsigned int)handoff->blocks[block][i]);
        putchar('\n');
        handoff->ready[block] = false;
    }
}

int main(void)
{
    struct DmaHandoff handoff = {0};
    for (size_t i = 0; i < BLOCK_SIZE; ++i) handoff.blocks[0][i] = (uint8_t)(i + 1U);
    simulated_dma_complete(&handoff, BLOCK_SIZE);
    process_ready(&handoff);

    /* TRY: 解释消费者太慢、两个 block 都 ready 时应该如何统计溢出。 */
    return 0;
}
