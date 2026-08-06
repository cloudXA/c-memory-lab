#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef bool (*uart_write_fn)(void *context, const uint8_t *data, size_t length);

struct UartPort {
    uart_write_fn write;
    void *context;
};

static bool console_send(struct UartPort *port, const char *text)
{
    size_t length = 0U;
    while (text[length] != '\0') length += 1U;
    return port != NULL && port->write != NULL &&
           port->write(port->context, (const uint8_t *)text, length);
}

static bool host_uart_write(void *context, const uint8_t *data, size_t length)
{
    FILE *stream = context;
    return fwrite(data, 1U, length, stream) == length;
}

int main(void)
{
    struct UartPort port = {.write = host_uart_write, .context = stdout};
    if (!console_send(&port, "portable uart interface\n")) return 1;

    /* TRY: STM32 适配层如何把 write 实现为 HAL_UART_Transmit？ */
    return 0;
}
