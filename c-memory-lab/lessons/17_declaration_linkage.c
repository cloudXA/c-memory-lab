#include <stdio.h>

int shared_counter = 0;             /* 定义：分配存储。 */
extern int shared_counter;          /* 声明：说明对象存在于某处。 */
static int file_private_counter = 0; /* 只在当前翻译单元可见。 */

int increment(int value);           /* 函数声明。 */

int increment(int value)            /* 函数定义。 */
{
    shared_counter += value;
    file_private_counter += 1;
    return shared_counter;
}

int main(void)
{
    int result = increment(3);
    printf("shared=%d, calls=%d\n", result, file_private_counter);
    result = increment(4);
    printf("shared=%d, calls=%d\n", result, file_private_counter);

    /* TRY: 运行 cc -c 只编译，再用 cc 链接；观察 .o 文件。 */
    return 0;
}
// shared=3, calls=1
// shared=7, calls=2