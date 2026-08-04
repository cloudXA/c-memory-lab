#include <stdio.h>

int main(void)
{
    int values[4] = {10, 20, 30, 40};

    printf("数组总大小=%zu，单个元素大小=%zu\n", sizeof values, sizeof values[0]);
    for (size_t i = 0; i < 4; ++i) {
        printf("values[%zu]: 地址=%p, 值=%d, 指针写法=%d\n",
               i, (void *)&values[i], values[i], *(values + i));
    }

    printf("\nvalues       = %p\n", (void *)values);
    printf("&values[0]   = %p\n", (void *)&values[0]);
    printf("values + 1   = %p\n", (void *)(values + 1));

    /* TRY: 用一个 int *p 遍历数组，不允许出现 values[i]。 */
    return 0;
}
