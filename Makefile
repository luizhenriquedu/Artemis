CC = gcc
CFLAGS = -g -O2
CFILES = $(shell find . -name "*.c")
OUT = out/art

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(OUT)
	./$(OUT) examples/main.art