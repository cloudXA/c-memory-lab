#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const size_t count = 5;
    int *p = malloc(count * sizeof(*p));

    if (p == NULL) {
        fprintf(stderr, "内存申请失败\n");
        return 1;
    }

    printf("指针对象：&p=%p, sizeof(p)=%zu\n", (void *)&p, sizeof p);
    printf("动态存储：p=%p, 请求字节数=%zu\n", (void *)p, count * sizeof(*p));

    for (size_t i = 0; i < count; ++i) {
        p[i] = (int)(i + 1) * 10;
        printf("p[%zu]: 地址=%p, 值=%d\n", i, (void *)&p[i], p[i]);
    }

    free(p);
    p = NULL;
    printf("free 后将 p 设为 %p；p 对象本身仍然存在。\n", (void *)p);

    /* TRY: 新建别名 int *alias = p（在 free 前），解释 free 后 alias 的状态。 */
    return 0;
}
