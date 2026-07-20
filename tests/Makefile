CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0

test_string_copy_padded: test_string_copy_padded.c
	$(CC) $(CFLAGS) -o $@ $<

test: test_string_copy_padded
	./test_string_copy_padded

clean:
	rm -f test_string_copy_padded

.PHONY: test clean
