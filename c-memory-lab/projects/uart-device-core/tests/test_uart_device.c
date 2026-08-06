#include "uart_device.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct Capture {
    struct UartFrame last;
    unsigned int calls;
    uint8_t accepted_command;
};

static bool capture_handler(const struct UartFrame *frame, void *context)
{
    struct Capture *capture = context;
    capture->last = *frame;
    capture->calls += 1U;
    return frame->command == capture->accepted_command;
}

static size_t make_frame(uint8_t command, const uint8_t *payload, size_t length,
                         uint8_t output[UART_DEVICE_MAX_PAYLOAD + 4U])
{
    size_t written = uart_frame_encode(command, payload, length,
                                       output, UART_DEVICE_MAX_PAYLOAD + 4U);
    assert(written > 0U);
    return written;
}

static void test_valid_and_partial_frame(void)
{
    struct UartDevice device;
    struct Capture capture = {.accepted_command = 0x10U};
    const uint8_t payload[] = {1U, 2U, 3U};
    uint8_t frame[UART_DEVICE_MAX_PAYLOAD + 4U];
    size_t length = make_frame(0x10U, payload, sizeof payload, frame);

    uart_device_init(&device, capture_handler, &capture);
    assert(uart_device_feed(&device, frame, 2U) == 2U);
    assert(uart_device_process(&device) == 2U);
    assert(capture.calls == 0U);

    assert(uart_device_feed(&device, &frame[2], length - 2U) == length - 2U);
    assert(uart_device_process(&device) == length - 2U);
    assert(capture.calls == 1U);
    assert(capture.last.command == 0x10U);
    assert(capture.last.payload_length == sizeof payload);
    assert(capture.last.payload[2] == 3U);
}

static void test_noise_bad_checksum_and_recovery(void)
{
    struct UartDevice device;
    struct Capture capture = {.accepted_command = 0x20U};
    uint8_t bad[UART_DEVICE_MAX_PAYLOAD + 4U];
    uint8_t good[UART_DEVICE_MAX_PAYLOAD + 4U];
    const uint8_t payload[] = {9U};
    size_t bad_length = make_frame(0x20U, payload, sizeof payload, bad);
    size_t good_length = make_frame(0x20U, payload, sizeof payload, good);
    const uint8_t noise[] = {0U, 1U, 2U};

    bad[bad_length - 1U] ^= 1U;
    uart_device_init(&device, capture_handler, &capture);
    (void)uart_device_feed(&device, noise, sizeof noise);
    (void)uart_device_feed(&device, bad, bad_length);
    (void)uart_device_feed(&device, good, good_length);
    (void)uart_device_process(&device);

    assert(capture.calls == 1U);
    assert(device.stats.checksum_errors == 1U);
    assert(device.stats.frames_valid == 1U);
}

static void test_rejected_command(void)
{
    struct UartDevice device;
    struct Capture capture = {.accepted_command = 0x10U};
    uint8_t frame[UART_DEVICE_MAX_PAYLOAD + 4U];
    size_t length = make_frame(0x99U, NULL, 0U, frame);

    uart_device_init(&device, capture_handler, &capture);
    (void)uart_device_feed(&device, frame, length);
    (void)uart_device_process(&device);
    assert(capture.calls == 1U);
    assert(device.stats.commands_rejected == 1U);
}

static void test_rx_overflow(void)
{
    struct UartDevice device;
    struct Capture capture = {.accepted_command = 0x10U};
    uart_device_init(&device, capture_handler, &capture);

    for (size_t i = 0; i < UART_DEVICE_RX_CAPACITY; ++i)
        assert(uart_device_feed_byte(&device, 0U));
    assert(!uart_device_feed_byte(&device, 0U));
    assert(device.stats.bytes_dropped == 1U);
}

int main(void)
{
    test_valid_and_partial_frame();
    test_noise_bad_checksum_and_recovery();
    test_rejected_command();
    test_rx_overflow();
    puts("uart-device-core: all tests passed");
    return 0;
}
