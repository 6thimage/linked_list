CC=clang
CFLAGS=-std=gnu11 -Weverything -O3 -g
#CFLAGS+=-fsanitize=undefined,integer
#CFLAGS+=-fsanitize=address -fno-omit-frame-pointer
#CFLAGS+=-fsanitize=memory -fno-omit-frame-pointer

default: all

test: test.c linked_list.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) -o $@ $^

benchmark: benchmark.c linked_list.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean

all: test benchmark

clean:
	@if [ -f test ]; then rm test; fi
	@if [ -f benchmark ]; then rm benchmark; fi


