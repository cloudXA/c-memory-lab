#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define POOL_CAPACITY 4U

struct Message {
    int value;
};

struct Slot {
    struct Message message;
    bool used;
};

static struct Slot pool[POOL_CAPACITY];

static struct Message *pool_allocate(void)
{
    for (size_t i = 0; i < POOL_CAPACITY; ++i) {
        if (!pool[i].used) {
            pool[i].used = true;
            return &pool[i].message;
        }
    }
    return NULL;
}

static bool pool_release(struct Message *message)
{
    for (size_t i = 0; i < POOL_CAPACITY; ++i) {
        if (&pool[i].message == message && pool[i].used) {
            pool[i].used = false;
            return true;
        }
    }
    return false;
}

int main(void)
{
    struct Message *message = pool_allocate();
    if (message == NULL) {
        return 1;
    }
    message->value = 42;
    printf("message=%d released=%s\n",
           message->value, pool_release(message) ? "yes" : "no");

    /* TRY: 分配 5 次并记录池满行为，再测试重复释放。 */
    return 0;
}
