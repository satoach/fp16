CFLAGS=-Wall -std=c11 -g
TARGET=target
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

$(TARGET): $(OBJS)
	cc -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(TARGET) *.o

test: $(TARGET)
	bash ./test.sh

.PHONY: clean test
