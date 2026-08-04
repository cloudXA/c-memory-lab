#include <stdio.h>
#include <stdlib.h>

static int allocate_one(int **out)
{
    *out = malloc(sizeof(**out));
    if (*out == NULL) {
        return 0;
    }

    **out = 42;
    return 1;
}

int main(void)
{
    int x = 10;
    int *p = &x;
    int **pp = &p;

    printf("x:  &x=%p,  x=%d\n", (void *)&x, x);
    printf("p:  &p=%p,  p=%p,  *p=%d\n", (void *)&p, (void *)p, *p);
    printf("pp: &pp=%p, pp=%p, *pp=%p, **pp=%d\n\n",
           (void *)&pp, (void *)pp, (void *)*pp, **pp);

    int *heap_number = NULL;
    printf("调用前：&heap_number=%p, heap_number=%p\n",
           (void *)&heap_number, (void *)heap_number);

    if (!allocate_one(&heap_number)) {
        fprintf(stderr, "内存申请失败\n");
        return 1;
    }

    printf("调用后：heap_number=%p, *heap_number=%d\n",
           (void *)heap_number, *heap_number);
    free(heap_number);
    heap_number = NULL;

    /* TRY: 画出 allocate_one 执行时 out、heap_number 和堆对象三层关系。 */
    return 0;
}
