#include <stdio.h>

static int file_only_value = 10;

static int next_id(void)
{
    static int current = 0;
    current += 1;
    return current;
}

int main(void)
{
    int automatic = 20;
    int first = next_id();
    int second = next_id();
    int third = next_id();

    printf("automatic: 地址=%p, 值=%d\n", (void *)&automatic, automatic);
    printf("file static: 地址=%p, 值=%d\n", (void *)&file_only_value, file_only_value);
    printf("连续调用 next_id: %d %d %d\n", first, second, third);

    /* TRY: 解释局部 static 为何离开函数后仍保留值，但名字仍只在函数内可见。 */
    return 0;
}
