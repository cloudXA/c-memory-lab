#include "uart_device.h"

#include <string.h>

static void parser_reset(struct UartDevice *device)
{
    device->parse_state = UART_WAIT_HEADER;
    device->frame.command = 0U;
    device->frame.payload_length = 0U;
    device->payload_index = 0U;
    device->checksum = 0U;
}

void uart_device_init(struct UartDevice *device,
                      uart_command_handler handler,
                      void *handler_context)
{
    if (device == NULL) return;
    memset(device, 0, sizeof(*device));
    device->handler = handler;
    device->handler_context = handler_context;
    parser_reset(device);
}

bool uart_device_feed_byte(struct UartDevice *device, uint8_t byte)
{
    if (device == NULL) return false;
    device->stats.bytes_received += 1U;
    if (device->rx_count == UART_DEVICE_RX_CAPACITY) {
        device->stats.bytes_dropped += 1U;
        return false;
    }
    device->rx[device->rx_head] = byte;
    device->rx_head = (device->rx_head + 1U) % UART_DEVICE_RX_CAPACITY;
    device->rx_count += 1U;
    return true;
}

size_t uart_device_feed(struct UartDevice *device,
                        const uint8_t *bytes, size_t length)
{
    if (device == NULL || (length > 0U && bytes == NULL)) return 0U;
    size_t accepted = 0U;
    for (size_t i = 0; i < length; ++i) {
        if (!uart_device_feed_byte(device, bytes[i])) break;
        accepted += 1U;
    }
    return accepted;
}

static bool ring_pop(struct UartDevice *device, uint8_t *out)
{
    if (device->rx_count == 0U || out == NULL) return false;
    *out = device->rx[device->rx_tail];
    device->rx_tail = (device->rx_tail + 1U) % UART_DEVICE_RX_CAPACITY;
    device->rx_count -= 1U;
    return true;
}

static void deliver_frame(struct UartDevice *device)
{
    device->stats.frames_valid += 1U;
    if (device->handler == NULL ||
        !device->handler(&device->frame, device->handler_context)) {
        device->stats.commands_rejected += 1U;
    }
}

static void parser_feed(struct UartDevice *device, uint8_t byte)
{
    switch (device->parse_state) {
    case UART_WAIT_HEADER:
        if (byte == UART_DEVICE_HEADER) device->parse_state = UART_READ_LENGTH;
        break;

    case UART_READ_LENGTH:
        if (byte > UART_DEVICE_MAX_PAYLOAD) {
            device->stats.length_errors += 1U;
            parser_reset(device);
            if (byte == UART_DEVICE_HEADER) device->parse_state = UART_READ_LENGTH;
            break;
        }
        device->frame.payload_length = byte;
        device->checksum = byte;
        device->parse_state = UART_READ_COMMAND;
        break;

    case UART_READ_COMMAND:
        device->frame.command = byte;
        device->checksum = (uint8_t)(device->checksum + byte);
        device->payload_index = 0U;
        device->parse_state = device->frame.payload_length == 0U
                            ? UART_READ_CHECKSUM : UART_READ_PAYLOAD;
        break;

    case UART_READ_PAYLOAD:
        device->frame.payload[device->payload_index++] = byte;
        device->checksum = (uint8_t)(device->checksum + byte);
        if (device->payload_index == device->frame.payload_length)
            device->parse_state = UART_READ_CHECKSUM;
        break;

    case UART_READ_CHECKSUM:
        if (byte == device->checksum) deliver_frame(device);
        else device->stats.checksum_errors += 1U;
        parser_reset(device);
        if (byte == UART_DEVICE_HEADER) device->parse_state = UART_READ_LENGTH;
        break;
    }
}

size_t uart_device_process(struct UartDevice *device)
{
    if (device == NULL) return 0U;
    size_t processed = 0U;
    uint8_t byte = 0U;
    while (ring_pop(device, &byte)) {
        parser_feed(device, byte);
        processed += 1U;
    }
    return processed;
}

const struct UartDeviceStats *uart_device_stats(const struct UartDevice *device)
{
    return device == NULL ? NULL : &device->stats;
}

size_t uart_frame_encode(uint8_t command,
                         const uint8_t *payload, size_t payload_length,
                         uint8_t *output, size_t output_capacity)
{
    size_t required = payload_length + 4U;
    if (payload_length > UART_DEVICE_MAX_PAYLOAD || output == NULL ||
        output_capacity < required || (payload_length > 0U && payload == NULL))
        return 0U;

    output[0] = UART_DEVICE_HEADER;
    output[1] = (uint8_t)payload_length;
    output[2] = command;
    uint8_t sum = (uint8_t)(output[1] + output[2]);
    for (size_t i = 0; i < payload_length; ++i) {
        output[3U + i] = payload[i];
        sum = (uint8_t)(sum + payload[i]);
    }
    output[3U + payload_length] = sum;
    return required;
}
