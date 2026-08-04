#include <stdio.h>

static const char *classify_temperature(int value)
{
    if (value < 0) {
        return "freezing";
    }
    if (value < 20) {
        return "cool";
    }
    if (value < 30) {
        return "warm";
    }
    return "hot";
}

int main(void)
{
    const int samples[] = {-5, 8, 23, 35};
    const size_t count = sizeof samples / sizeof samples[0];

    for (size_t i = 0; i < count; ++i) {
        printf("%d -> %s\n", samples[i], classify_temperature(samples[i]));
    }

    /* TRY: 用 switch 实现 0=关闭、1=启动、2=故障三种设备状态。 */
    return 0;
}
