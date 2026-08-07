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

    int *p = values;
    for (size_t i = 0; i < 4; ++i) {
        printf("values[%zu]: 地址=%p, 值=%d\n",
               i, (void *)(p + i), *(p + i));
    }

    return 0;
}
//数组总大小=16，单个元素大小=10
// values[0]: 地址=0x10000, 值=10, 指针写法=10
// values[1]: 地址=0x10004, 值=20, 指针写法=20
// values[2]: 地址=0x10008, 值=30, 指针写法=30
// values[3]: 地址=0x1000c, 值=40, 指针写法=40

//values       = 0x10000
// &values[0]   = 0x10000
// values + 1   = 0x10004

// values[0]: 地址=0x10000, 值=10, 指针写法=10
// values[1]: 地址=0x10004, 值=20, 指针写法=20
// values[2]: 地址=0x10008, 值=30, 指针写法=30
// values[3]: 地址=0x1000c, 值=40, 指针写法=40









// 数组总大小=16，单个元素大小=4
// values[0]: 地址=0x10000, 值=10, 指针写法=10
// values[1]: 地址=0x10004, 值=20, 指针写法=20
// values[2]: 地址=0x10008, 值=30, 指针写法=30
// values[3]: 地址=0x1000c, 值=40, 指针写法=40

// values       = 0x10000
// &values[0]   = 0x10000
// values + 1   = 0x10004
