#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef bool (*command_handler)(const uint8_t *payload, size_t length, void *context);

struct CommandEntry {
    uint8_t command;
    command_handler handler;
};

static bool set_led(const uint8_t *payload, size_t length, void *context)
{
    bool *led = context;
    if (payload == NULL || length != 1U || payload[0] > 1U) return false;
    *led = payload[0] != 0U;
    return true;
}

static bool dispatch(const struct CommandEntry *table, size_t count,
                     uint8_t command, const uint8_t *payload, size_t length,
                     void *context)
{
    for (size_t i = 0; i < count; ++i) {
        if (table[i].command == command)
            return table[i].handler(payload, length, context);
    }
    return false;
}

int main(void)
{
    const struct CommandEntry table[] = {{0x10U, set_led}};
    const uint8_t payload[] = {1U};
    bool led = false;

    bool ok = dispatch(table, sizeof table / sizeof table[0],
                       0x10U, payload, sizeof payload, &led);
    printf("ok=%s led=%s\n", ok ? "yes" : "no", led ? "on" : "off");

    /* TRY: 增加 GET_STATUS 命令，且不修改 dispatch 函数。 */
    return 0;
}
