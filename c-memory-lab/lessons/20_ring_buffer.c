#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFER_CAPACITY 4U

struct RingBuffer {
    uint8_t data[BUFFER_CAPACITY];
    size_t head;
    size_t tail;
    size_t count;
};

static bool ring_push(struct RingBuffer *buffer, uint8_t value)
{
    if (buffer->count == BUFFER_CAPACITY) {
        return false;
    }
    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1U) % BUFFER_CAPACITY;
    buffer->count += 1U;
    return true;
}

static bool ring_pop(struct RingBuffer *buffer, uint8_t *out)
{
    if (buffer->count == 0U || out == NULL) {
        return false;
    }
    *out = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1U) % BUFFER_CAPACITY;
    buffer->count -= 1U;
    return true;
}

int main(void)
{
    struct RingBuffer buffer = {0};
    uint8_t value = 0U;

    for (uint8_t i = 1U; i <= 4U; ++i) {
        printf("push %u: %s\n", (unsigned int)i, ring_push(&buffer, i) ? "ok" : "full");
    }
    while (ring_pop(&buffer, &value)) {
        printf("pop %u\n", (unsigned int)value);
    }

    /* TRY: 交替 push/pop，使 head 和 tail 至少绕回数组开头一次。 */
    return 0;
}
