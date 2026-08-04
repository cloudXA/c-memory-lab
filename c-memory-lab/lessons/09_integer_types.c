#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t byte = UINT8_MAX;
    int promoted = byte + 1;
    int negative = -1;
    unsigned int positive = 1U;

    printf("uint8_t max=%u, 加 1 后经整数提升=%d\n", (unsigned int)byte, promoted);
    printf("INT_MAX=%d, UINT_MAX=%u\n", INT_MAX, UINT_MAX);
    unsigned int converted_negative = (unsigned int)negative;
    printf("-1 转 unsigned=%u；它 < 1U 的结果=%s\n",
           converted_negative, converted_negative < positive ? "true" : "false");

    /* TRY: 编译时保留 -Wconversion，观察不同类型赋值产生的警告。 */
    return 0;
}
