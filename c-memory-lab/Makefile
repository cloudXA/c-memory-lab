CC := cc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Wconversion -g -O0
SOURCES := $(wildcard lessons/*.c)
TARGETS := $(patsubst lessons/%.c,build/%,$(SOURCES))

.PHONY: all clean sanitize address-sanitize test verify module-demo uart-core list run help

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
	@echo "All lesson programs passed."

verify:
	$(MAKE) clean all
	$(MAKE) test
	$(MAKE) module-demo
	$(MAKE) uart-core
	@echo "Full verification passed."

module-demo:
	$(MAKE) -C examples/multi_file clean all

uart-core:
	$(MAKE) -C projects/uart-device-core clean test

list:
	@for target in $(TARGETS); do echo "$$target"; done

run:
	@if [ -z "$(LESSON)" ]; then \
		echo "Usage: make run LESSON=03_arrays"; \
		exit 2; \
	fi
	@if [ ! -f "lessons/$(LESSON).c" ]; then \
		echo "Unknown lesson: $(LESSON)"; \
		echo "Run 'make list' to see available lesson names."; \
		exit 2; \
	fi
	$(MAKE) "build/$(LESSON)"
	@echo "--- Running build/$(LESSON) ---"
	@"build/$(LESSON)"

help:
	@echo "make all                            Build all lessons"
	@echo "make run LESSON=03_arrays           Build and run one lesson"
	@echo "make test                           Run all lessons"
	@echo "make sanitize && make test          Rebuild with UBSan and run"
	@echo "make address-sanitize && make test  Rebuild with ASan+UBSan"
	@echo "make uart-core                      Test the UART project"
	@echo "make verify                         Verify lessons and projects"
	@echo "make clean                          Remove generated files"

clean:
	rm -rf build
