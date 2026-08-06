#include <stdio.h>
#include <stdlib.h>

static int initialized_data = 10;
static int zero_initialized_data;
static const int read_only_data = 30;

int main(void)
{
    int automatic_data = 40;
    int *allocated_data = malloc(sizeof(*allocated_data));

    if (allocated_data == NULL) {
        return 1;
    }
    *allocated_data = 50;

    printf("initialized static  %p value=%d\n", (void *)&initialized_data, initialized_data);
    printf("zero static         %p value=%d\n", (void *)&zero_initialized_data, zero_initialized_data);
    printf("const static        %p value=%d\n", (const void *)&read_only_data, read_only_data);
    printf("automatic           %p value=%d\n", (void *)&automatic_data, automatic_data);
    printf("allocated           %p value=%d\n", (void *)allocated_data, *allocated_data);

    free(allocated_data);

    /* TRY: 使用 size 或 nm 查看可执行文件中的 text/data/bss 符号。 */
    return 0;
}
