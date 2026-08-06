#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static volatile bool event_pending;
static volatile uint32_t event_count;

static void simulated_isr(void)
{
    event_count += 1U;
    event_pending = true;
}

static void main_loop_once(void)
{
    if (event_pending) {
        event_pending = false;
        printf("process event, count snapshot=%u\n", event_count);
    }
}

int main(void)
{
    simulated_isr();
    main_loop_once();

    /*
     * volatile 只要求实际读写，不保证 event_count += 1 是原子的，也不
     * 保证检查并清除 event_pending 不会与真正的 ISR 交错。
     */
    /* TRY: 写出使用临界区取得一致快照的伪代码。 */
    return 0;
}
