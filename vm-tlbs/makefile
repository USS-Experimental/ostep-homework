CC=gcc
CFLAGS=-Wall -O0
TARGET=tlb.out
SOURCE=tlb.c
PYTHON_SCRIPT=run_tlb.py
PYTHON=python3

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET) result.png

