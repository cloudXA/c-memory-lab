#include <stdio.h>

enum State {
    STATE_OFF,
    STATE_STARTING,
    STATE_RUNNING,
    STATE_ERROR
};

enum Event {
    EVENT_POWER_ON,
    EVENT_READY,
    EVENT_FAILURE,
    EVENT_RESET
};

static enum State transition(enum State state, enum Event event)
{
    switch (state) {
    case STATE_OFF:
        return event == EVENT_POWER_ON ? STATE_STARTING : state;
    case STATE_STARTING:
        return event == EVENT_READY ? STATE_RUNNING :
               event == EVENT_FAILURE ? STATE_ERROR : state;
    case STATE_RUNNING:
        return event == EVENT_FAILURE ? STATE_ERROR : state;
    case STATE_ERROR:
        return event == EVENT_RESET ? STATE_OFF : state;
    }
    return STATE_ERROR;
}

int main(void)
{
    const enum Event events[] = {EVENT_POWER_ON, EVENT_READY, EVENT_FAILURE, EVENT_RESET};
    enum State state = STATE_OFF;

    for (size_t i = 0; i < sizeof events / sizeof events[0]; ++i) {
        enum State before = state;
        state = transition(state, events[i]);
        printf("state %d + event %d -> state %d\n", before, events[i], state);
    }

    /* TRY: 增加 STOPPING 状态和 POWER_OFF 事件，并列出所有合法迁移。 */
    return 0;
}
