#include <stddef.h>
#include <stdio.h>

typedef void (*value_callback)(int value, void *context);

static void for_each(const int *values, size_t count,
                     value_callback callback, void *context)
{
    for (size_t i = 0; i < count; ++i) {
        callback(values[i], context);
    }
}

static void add_to_total(int value, void *context)
{
    int *total = context;
    *total += value;
}

static void print_if_greater(int value, void *context)
{
    int *threshold = context;
    if (value > *threshold) {
        printf("%d\n", value);
    }
}

int main(void)
{
    const int values[] = {2, 4, 6, 8};
    int total = 0;
    int threshold = 5;

    for_each(values, sizeof values / sizeof values[0], add_to_total, &total);
    printf("total=%d\n", total);

    /* TRY: 再写一个回调，只打印大于 context 所指阈值的元素。 */
    for_each(values, sizeof values / sizeof values[0], print_if_greater, &threshold);

    return 0;
}
// total=20