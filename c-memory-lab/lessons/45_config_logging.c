#include <stdio.h>

#define UART_BAUD_RATE 115200U
#define RX_CAPACITY 128U

enum LogLevel { LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG };

#ifndef ACTIVE_LOG_LEVEL
#define ACTIVE_LOG_LEVEL LOG_INFO
#endif

#define LOG(level, ...)                         \
    do {                                        \
        if ((level) <= ACTIVE_LOG_LEVEL) {      \
            printf(__VA_ARGS__);                \
            putchar('\n');                      \
        }                                       \
    } while (0)

int main(void)
{
    LOG(LOG_INFO, "uart baud=%u rx_capacity=%u", UART_BAUD_RATE, RX_CAPACITY);
    LOG(LOG_DEBUG, "debug details hidden by default");

    /* TRY: 使用 -DACTIVE_LOG_LEVEL=LOG_DEBUG 编译并观察输出变化。 */
    return 0;
}
