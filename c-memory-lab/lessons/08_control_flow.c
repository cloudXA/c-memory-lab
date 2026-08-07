#include <stdio.h>

static const char *classify_temperature(int value) // 从右往左读：一个指针，指向 char，指向的内容是 const（只读）。
{
    // if (value < 0) {
    //     return "freezing";
    // }
    // if (value < 20) {
    //     return "cool";
    // }
    // if (value < 30) {
    //     return "warm";
    // }
    // return "hot";

    switch (value)
    {
        case -5:
            return "freezing";
        case 8:
            return "cool";
        case 23:
            return "warm";
        case 35:
            return "hot";
    }
}

int main(void)
{
    const int samples[] = {-5, 8, 23, 35};
    const size_t count = sizeof samples / sizeof samples[0];

    for (size_t i = 0; i < count; ++i) {
        printf("%d -> %s, %p\n", samples[i], classify_temperature(samples[i]), &samples[i]);
    }

    /* TRY: 用 switch 实现 0=关闭、1=启动、2=故障三种设备状态。 */
    return 0;
}
// -5 -> freezing
// 8 -> cool
// 23 -> warm
// 35 -> hot