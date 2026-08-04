#include <stdio.h>

static void change_value(int copy)
{
    printf("change_value: &copy=%p\n", (void *)&copy);
    copy = 100;
}

static void change_through_pointer(int *address)
{
    printf("change_through_pointer: &address=%p, address=%p\n",
           (void *)&address, (void *)address);
    *address = 200;
}

int main(void)
{
    int x = 42;

    printf("main: &x=%p, x=%d\n", (void *)&x, x);
    change_value(x);
    printf("按值调用后 x=%d\n", x);
    change_through_pointer(&x);
    printf("传地址调用后 x=%d\n", x);

    /* TRY: 画出调用 change_through_pointer 时 x 和 address 两个对象。 */
    return 0;
}
