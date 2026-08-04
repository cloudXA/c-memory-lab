#include <stdint.h>
#include <stdio.h>

static void encode_u16_be(uint16_t value, uint8_t out[2])
{
    out[0] = (uint8_t)(value >> 8U);
    out[1] = (uint8_t)(value & UINT16_C(0xff));
}

static uint16_t decode_u16_be(const uint8_t input[2])
{
    return (uint16_t)((uint16_t)input[0] << 8U) | (uint16_t)input[1];
}

int main(void)
{
    uint16_t value = UINT16_C(0x1234);
    uint8_t encoded[2];

    encode_u16_be(value, encoded);
    printf("encoded: %02x %02x\n", encoded[0], encoded[1]);
    printf("decoded: %#06x\n", decode_u16_be(encoded));

    const uint8_t *host_bytes = (const uint8_t *)&value;
    printf("本机内存顺序: %02x %02x\n", host_bytes[0], host_bytes[1]);

    /* TRY: 实现 uint32_t 的大端编码和解码。 */
    return 0;
}
