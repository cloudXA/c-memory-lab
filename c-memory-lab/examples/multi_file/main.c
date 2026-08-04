#include "counter.h"

#include <stdio.h>

int main(void)
{
    struct Counter counter;
    counter_init(&counter, 10);

    printf("%d\n", counter_increment(&counter));
    printf("%d\n", counter_increment(&counter));
    return 0;
}
