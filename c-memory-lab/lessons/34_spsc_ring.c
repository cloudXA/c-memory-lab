#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define RING_CAPACITY 8U

struct Ring {
    uint8_t data[RING_CAPACITY];
    size_t head;
    size_t tail;
};

static bool ring_push(struct Ring *ring, uint8_t value)
{
    size_t next = (ring->head + 1U) % RING_CAPACITY;
    if (next == ring->tail) {
        return false;
    }
    ring->data[ring->head] = value;
    ring->head = next;
    return true;
}

static bool ring_pop(struct Ring *ring, uint8_t *out)
{
    if (ring->tail == ring->head || out == NULL) {
        return false;
    }
    *out = ring->data[ring->tail];
    ring->tail = (ring->tail + 1U) % RING_CAPACITY;
    return true;
}

int main(void)
{
    struct Ring ring = {0};
    const uint8_t input[] = {'U', 'A', 'R', 'T'};
    uint8_t value = 0U;

    for (size_t i = 0; i < sizeof input; ++i) {
        (void)ring_push(&ring, input[i]);
    }
    while (ring_pop(&ring, &value)) {
        putchar((int)value);
    }
    putchar('\n');

    /* TRY: 说明浪费一个槽位如何区分空和满；再增加 overflow 计数。 */
    return 0;
}
