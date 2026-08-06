#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static void consume_chunk(const uint8_t *bytes, size_t length)
{
    printf("chunk length=%zu: ", length);
    for (size_t i = 0; i < length; ++i) {
        putchar((int)bytes[i]);
    }
    putchar('\n');
}

int main(void)
{
    const uint8_t chunk1[] = {'S', 'E'};
    const uint8_t chunk2[] = {'T', ' ', '1', '\n', 'G'};
    const uint8_t chunk3[] = {'E', 'T', '\n'};

    consume_chunk(chunk1, sizeof chunk1);
    consume_chunk(chunk2, sizeof chunk2);
    consume_chunk(chunk3, sizeof chunk3);

    printf("三次接收块包含两条命令；接收边界不等于消息边界。\n");
    /* TRY: 画出 SET 1 和 GET 如何跨越三个 chunk。 */
    return 0;
}
