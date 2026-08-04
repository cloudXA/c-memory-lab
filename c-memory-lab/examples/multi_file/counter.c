#include "counter.h"

static int normalize(int value)
{
    return value < 0 ? 0 : value;
}

void counter_init(struct Counter *counter, int initial_value)
{
    counter->value = normalize(initial_value);
}

int counter_increment(struct Counter *counter)
{
    counter->value += 1;
    return counter->value;
}
