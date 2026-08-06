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

    printf("指针对象：&p=%p, sizeof(p)=%zu, count*sizeof(*p)=%zu\n",
           (void *)&p, sizeof p, count * sizeof(*p));
    printf("动态存储：p=%p, 请求字节数=%zu\n", (void *)p, count * sizeof(*p));
    printf("*&p 等于 p，保存的动态存储地址=%p\n", (void *)*&p);

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

// 指针对象：&p=0x16f78ea38, sizeof(p)=8, count*sizeof(p)=20
// 动态存储：p=0x100e99c70, 请求字节数=20
// p[0]: 地址=0x100e99c70, 值=10
// p[1]: 地址=0x100e99c74, 值=20
// p[2]: 地址=0x100e99c78, 值=30
// p[3]: 地址=0x100e99c7c, 值=40
// p[4]: 地址=0x100e99c80, 值=50
// free 后将 p 设为空指针（%p 可能显示 0x0 或 (nil)）；p 对象本身仍存在。
