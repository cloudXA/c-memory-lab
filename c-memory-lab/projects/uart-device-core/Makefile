CC := cc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Werror -g -O0
CPPFLAGS := -Iinclude
BUILD := build
TARGET := $(BUILD)/test_uart_device
SOURCES := src/uart_device.c tests/test_uart_device.c

.PHONY: all test sanitize clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/uart_device.h | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

$(BUILD):
	mkdir -p $(BUILD)

test: all
	./$(TARGET)

sanitize: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
sanitize: clean test

clean:
	rm -rf $(BUILD)
