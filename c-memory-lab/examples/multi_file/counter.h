#ifndef COUNTER_H
#define COUNTER_H

struct Counter {
    int value;
};

void counter_init(struct Counter *counter, int initial_value);
int counter_increment(struct Counter *counter);

#endif
