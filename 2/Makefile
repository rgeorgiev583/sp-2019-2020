CFLAGS := -g

TARGETS := $(patsubst %.c, %, $(wildcard *.c))

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)