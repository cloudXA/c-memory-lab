#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

enum State { OFF, STARTING, RUNNING, ERROR_STATE };
enum Event { POWER_ON, READY, FAILURE, RESET };

static enum State transition(enum State state, enum Event event)
{
    if (state == OFF && event == POWER_ON) return STARTING;
    if (state == STARTING && event == READY) return RUNNING;
    if ((state == STARTING || state == RUNNING) && event == FAILURE)
        return ERROR_STATE;
    if (state == ERROR_STATE && event == RESET) return OFF;
    return state;
}

int main(void)
{
    assert(transition(OFF, POWER_ON) == STARTING);
    assert(transition(STARTING, READY) == RUNNING);
    assert(transition(RUNNING, FAILURE) == ERROR_STATE);
    assert(transition(ERROR_STATE, RESET) == OFF);
    assert(transition(OFF, READY) == OFF);
    puts("all host tests passed");

    /* TRY: 表驱动枚举所有 state/event 组合并记录预期状态。 */
    return 0;
}
