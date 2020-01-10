CFLAGS := -std=c99 -g

TARGETS := $(patsubst %.c, %, $(wildcard *.c))

.PHONY: all clean

all: $(TARGETS)

3-mmap: 3-mmap.c
	$(CC) -std=gnu99 -g $< -o $@

clean:
	$(RM) $(TARGETS)