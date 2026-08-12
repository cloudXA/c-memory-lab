#include <stdio.h>

int main(void)
{
    int x = 10;
    int y = 20;
    const int *pointer_to_const = &x;
    int *const const_pointer = &x;

    printf("pointer_to_const 指向的值=%d\n", *pointer_to_const);
    pointer_to_const = &y;
    printf("它可以改指向，现在值=%d\n", *pointer_to_const);

    *const_pointer = 99;
    printf("const_pointer 不能改指向，但能修改 x=%d\n", x);

    /* TRY: 分别尝试 *pointer_to_const = 1 和 const_pointer = &y，阅读编译错误。 */

    *pointer_to_const = 1;
    const_pointer = &y;
    return 0;
}
// pointer_to_const 指向的值=10
// 它可以改指向，现在值=20
// const_pointer 不能改指向，但能修改 x=99s