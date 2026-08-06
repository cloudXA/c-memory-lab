#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct LinkStats {
    uint32_t bytes_received;
    uint32_t valid_frames;
    uint32_t checksum_errors;
    uint32_t overflows;
    uint32_t timeouts;
};

static bool timed_out(uint32_t now, uint32_t last_byte, uint32_t timeout)
{
    return (uint32_t)(now - last_byte) >= timeout;
}

int main(void)
{
    struct LinkStats stats = {
        .bytes_received = 120U,
        .valid_frames = 8U,
        .checksum_errors = 2U,
        .overflows = 1U,
        .timeouts = 0U
    };

    if (timed_out(150U, 90U, 50U)) stats.timeouts += 1U;
    printf("rx=%u frames=%u crc=%u overflow=%u timeout=%u\n",
           stats.bytes_received, stats.valid_frames, stats.checksum_errors,
           stats.overflows, stats.timeouts);

    /* TRY: 为连续错误增加有限重试和退避状态，而不是无限重试。 */
    return 0;
}
