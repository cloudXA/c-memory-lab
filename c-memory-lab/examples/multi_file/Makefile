CC := cc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Wconversion -g -O0
OBJECTS := main.o counter.o

.PHONY: all clean

all: app

app: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

main.o: main.c counter.h
	$(CC) $(CFLAGS) -c main.c -o $@

counter.o: counter.c counter.h
	$(CC) $(CFLAGS) -c counter.c -o $@

clean:
	rm -f app $(OBJECTS)
