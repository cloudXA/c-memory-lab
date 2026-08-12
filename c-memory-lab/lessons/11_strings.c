#include <stdio.h>
#include <string.h>

int main(void)
{
    char editable[] = "sensor";
    const char *literal = "sensor";
    char destination[6];

    editable[0] = 'S';
    int written = snprintf(destination, sizeof destination, "%s-%d", editable, 7);

    printf("editable sizeof=%zu, strlen=%zu, 内容=%s\n",
           sizeof editable, strlen(editable), editable);
    printf("literal 指针大小=%zu, 指向字符串大小=%zu, 字符串长度=%zu\n", sizeof literal, sizeof (*literal), strlen(literal));
    printf("snprintf 返回=%d, 结果=%s\n", written, destination);
    

    /* TRY: 把 destination 改成 6 字节，检测 snprintf 是否发生截断。 */
    return 0;
}
// editable sizeof=7, strlen=6, 内容=Sensor
// literal 指针大小=8, 指向字符串大小=1, 字符串长度=6
// snprintf 返回=8, 结果=Sensor-7