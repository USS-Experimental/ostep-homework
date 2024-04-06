CC=gcc
CFLAGS=-Wall

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean

all: $(patsubst %.c,%.out,$(wildcard *.c))

clean:
	rm -f *.out
