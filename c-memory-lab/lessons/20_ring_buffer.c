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

/* 初始化：清零即可，无需单独函数，直接用 {0} 初始化。 */

static bool ring_is_empty(const struct RingBuffer *buffer)
{
    return buffer->count == 0U;
}

static bool ring_is_full(const struct RingBuffer *buffer)
{
    return buffer->count == BUFFER_CAPACITY;
}

/* 生产者：只管写入。满了返回 false，由调用者决定丢弃或重试。 */
static bool ring_push(struct RingBuffer *buffer, uint8_t value)
{
    if (ring_is_full(buffer)) {
        return false;
    }
    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1U) % BUFFER_CAPACITY;
    buffer->count += 1U;
    return true;
}

/* 消费者：只管读取。空了返回 false。 */
static bool ring_pop(struct RingBuffer *buffer, uint8_t *out)
{
    if (ring_is_empty(buffer) || out == NULL) {
        return false;
    }
    *out = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1U) % BUFFER_CAPACITY;
    buffer->count -= 1U;
    return true;
}

/* ---- 生产者角色：模拟外部数据源（如串口中断）不断 push ---- */
static void producer_task(struct RingBuffer *buffer, const uint8_t *data, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        if (ring_push(buffer, data[i])) {
            printf("producer push %u\n", (unsigned int)data[i]);
        } else {
            printf("producer push %u: full, dropped\n", (unsigned int)data[i]);
        }
    }
}

/* ---- 消费者角色：模拟主循环按自己的节奏 pop ---- */
static void consumer_task(struct RingBuffer *buffer, size_t n)
{
    uint8_t value = 0U;
    for (size_t i = 0; i < n; ++i) {
        if (ring_pop(buffer, &value)) {
            printf("consumer pop %u\n", (unsigned int)value);
        } else {
            printf("consumer pop: empty\n");
        }
    }
}

int main(void)
{
    struct RingBuffer buffer = {0};

    /* 生产者和消费者各管各的节奏，互不假设对方速度。 */
    const uint8_t incoming[] = {1, 2, 3, 4, 5, 6};

    producer_task(&buffer, incoming, 4);   /* 生产者先灌 4 个（刚好满） */
    consumer_task(&buffer, 2);             /* 消费者取 2 个，腾出空间 */
    producer_task(&buffer, incoming + 4, 2); /* 生产者再灌 2 个，head 绕回 */

    consumer_task(&buffer, 8);             /* 消费者把剩下的取完 */

    return 0;
}
// producer push 1
// producer push 2
// producer push 3
// producer push 4
// consumer pop 1
// consumer pop 2
// producer push 5
// producer push 6
// consumer pop 3
// consumer pop 4
// consumer pop 5
// consumer pop 6
// consumer pop: empty