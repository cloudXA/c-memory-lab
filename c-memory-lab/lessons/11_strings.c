#include <stdio.h>
#include <string.h>

int main(void)
{
    char editable[] = "sensor";
    const char *literal = "sensor";
    char destination[16];

    editable[0] = 'S';
    int written = snprintf(destination, sizeof destination, "%s-%d", editable, 7);

    printf("editable sizeof=%zu, strlen=%zu, 内容=%s\n",
           sizeof editable, strlen(editable), editable);
    printf("literal 指针大小=%zu, 字符串长度=%zu\n", sizeof literal, strlen(literal));
    printf("snprintf 返回=%d, 结果=%s\n", written, destination);

    /* TRY: 把 destination 改成 6 字节，检测 snprintf 是否发生截断。 */
    return 0;
}
