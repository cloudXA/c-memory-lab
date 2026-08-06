#ifndef UART_DEVICE_H
#define UART_DEVICE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define UART_DEVICE_HEADER UINT8_C(0xaa)
#define UART_DEVICE_MAX_PAYLOAD 16U
#define UART_DEVICE_RX_CAPACITY 64U

struct UartFrame {
    uint8_t command;
    uint8_t payload[UART_DEVICE_MAX_PAYLOAD];
    size_t payload_length;
};

struct UartDeviceStats {
    uint32_t bytes_received;
    uint32_t bytes_dropped;
    uint32_t frames_valid;
    uint32_t length_errors;
    uint32_t checksum_errors;
    uint32_t commands_rejected;
};

typedef bool (*uart_command_handler)(const struct UartFrame *frame, void *context);

enum UartParseState {
    UART_WAIT_HEADER,
    UART_READ_LENGTH,
    UART_READ_COMMAND,
    UART_READ_PAYLOAD,
    UART_READ_CHECKSUM
};

struct UartDevice {
    uint8_t rx[UART_DEVICE_RX_CAPACITY];
    size_t rx_head;
    size_t rx_tail;
    size_t rx_count;

    enum UartParseState parse_state;
    struct UartFrame frame;
    size_t payload_index;
    uint8_t checksum;

    uart_command_handler handler;
    void *handler_context;
    struct UartDeviceStats stats;
};

void uart_device_init(struct UartDevice *device,
                      uart_command_handler handler,
                      void *handler_context);

bool uart_device_feed_byte(struct UartDevice *device, uint8_t byte);
size_t uart_device_feed(struct UartDevice *device,
                        const uint8_t *bytes, size_t length);
size_t uart_device_process(struct UartDevice *device);
const struct UartDeviceStats *uart_device_stats(const struct UartDevice *device);

size_t uart_frame_encode(uint8_t command,
                         const uint8_t *payload, size_t payload_length,
                         uint8_t *output, size_t output_capacity);

#endif
