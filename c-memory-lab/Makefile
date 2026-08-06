CC := cc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Wconversion -g -O0
SOURCES := $(wildcard lessons/*.c)
TARGETS := $(patsubst lessons/%.c,build/%,$(SOURCES))

.PHONY: all clean sanitize address-sanitize test module-demo uart-core list

all: $(TARGETS)

build/%: lessons/%.c | build
	$(CC) $(CFLAGS) $< -o $@

build:
	mkdir -p build

sanitize: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
sanitize: clean all

address-sanitize: CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
address-sanitize: clean all

test: all
	@for target in $(TARGETS); do \
		echo "Running $$target"; \
		"$$target" >/dev/null || exit 1; \
	done

module-demo:
	$(MAKE) -C examples/multi_file clean all

uart-core:
	$(MAKE) -C projects/uart-device-core clean test

list:
	@for target in $(TARGETS); do echo "$$target"; done

clean:
	rm -rf build
