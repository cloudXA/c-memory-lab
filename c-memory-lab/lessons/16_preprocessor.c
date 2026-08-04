#include <stdint.h>
#include <stdio.h>

#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))
#define SQUARE_BAD(x) x * x
#define SQUARE(x) ((x) * (x))

int main(void)
{
    const int values[] = {1, 2, 3, 4};

    printf("数组元素数=%zu\n", ARRAY_COUNT(values));
    printf("错误宏 SQUARE_BAD(1 + 2)=%d\n", SQUARE_BAD(1 + 2));
    printf("加括号后 SQUARE(1 + 2)=%d\n", SQUARE(1 + 2));

#ifdef DEBUG
    printf("DEBUG 构建已开启\n");
#else
    printf("普通构建；可尝试 cc -DDEBUG ...\n");
#endif

    /* TRY: 用 cc -E lessons/16_preprocessor.c 查看预处理结果。 */
    return 0;
}
