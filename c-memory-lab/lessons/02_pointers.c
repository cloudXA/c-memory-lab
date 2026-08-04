#include <stdio.h>

int main(void)
{
    int x = 42;
    int *p = &x;

    printf("x   : 值=%d,  自己的地址=%p\n", x, (void *)&x);
    printf("p   : 值=%p, 自己的地址=%p, 大小=%zu\n",
           (void *)p, (void *)&p, sizeof p);
    printf("*p  : 值=%d,  它访问的地址=%p\n", *p, (void *)p);

    *p = 99;
    printf("执行 *p = 99 后：x=%d, *p=%d\n", x, *p);

    // TRY: 新建 int y，让 p 改为指向 y，再通过 p 修改 y
    int y = 10;
    p = &y;       // p 改为指向 y（p 现在存 y 的地址）
    *p = 88;      // 通过 p 修改 y
    printf("p 指向 y 后，*p = 88：y=%d, *p=%d, x=%d\n", y, *p, x);

    return 0;
}
