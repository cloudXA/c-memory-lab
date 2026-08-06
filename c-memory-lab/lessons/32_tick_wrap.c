#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool elapsed(uint32_t now, uint32_t start, uint32_t duration)
{
    return (uint32_t)(now - start) >= duration;
}

int main(void)
{
    uint32_t start = UINT32_MAX - UINT32_C(5);
    uint32_t before_wrap = UINT32_MAX - UINT32_C(1);
    uint32_t after_wrap = UINT32_C(4);

    printf("before wrap elapsed=%u done=%s\n",
           before_wrap - start,
           elapsed(before_wrap, start, 10U) ? "yes" : "no");
    printf("after wrap elapsed=%u done=%s\n",
           after_wrap - start,
           elapsed(after_wrap, start, 10U) ? "yes" : "no");

    /* TRY: 解释为什么 now >= start + duration 在回绕附近不可靠。 */
    return 0;
}
