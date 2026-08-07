#include <stddef.h>
#include <stdio.h>

struct Sample {
    char tag;
    char state;
    int count;
};

int main(void)
{
    struct Sample item = {'A', 100, 'Y'};

    printf("结构体地址=%p，总大小=%zu\n", (void *)&item, sizeof item);
    printf("tag:   地址=%p, 偏移=%zu, 大小=%zu\n",
           (void *)&item.tag, offsetof(struct Sample, tag), sizeof item.tag);
   
    printf("count: 地址=%p, 偏移=%zu, 大小=%zu\n",
           (void *)&item.count, offsetof(struct Sample, count), sizeof item.count);

    printf("state: 地址=%p, 偏移=%zu, 大小=%zu\n",
           (void *)&item.state, offsetof(struct Sample, state), sizeof item.state);



    /* TRY: 把两个 char 放在一起，重新编译并比较 sizeof。 */
    return 0;
}



