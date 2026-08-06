#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FRAME_HEADER UINT8_C(0xaa)
#define MAX_PAYLOAD 8U

static uint8_t checksum(const uint8_t *bytes, size_t length)
{
    uint8_t sum = 0U;
    for (size_t i = 0; i < length; ++i) {
        sum = (uint8_t)(sum + bytes[i]);
    }
    return sum;
}

static bool encode_frame(uint8_t command, const uint8_t *payload, size_t length,
                         uint8_t *out, size_t capacity, size_t *written)
{
    if (out == NULL || written == NULL || length > MAX_PAYLOAD ||
        capacity < length + 4U || (length > 0U && payload == NULL)) {
        return false;
    }
    out[0] = FRAME_HEADER;
    out[1] = (uint8_t)length;
    out[2] = command;
    for (size_t i = 0; i < length; ++i) out[3U + i] = payload[i];
    out[3U + length] = checksum(&out[1], length + 2U);
    *written = length + 4U;
    return true;
}

int main(void)
{
    const uint8_t payload[] = {1U, 2U, 3U};
    uint8_t frame[16];
    size_t length = 0U;

    if (!encode_frame(0x10U, payload, sizeof payload,
                      frame, sizeof frame, &length)) return 1;
    for (size_t i = 0; i < length; ++i) printf("%02x ", (unsigned int)frame[i]);
    putchar('\n');

    /* TRY: 手算校验和，再翻转一个 payload 字节验证校验失败。 */
    return 0;
}
