CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0

test_string_copy_padded: test_string_copy_padded.c
	$(CC) $(CFLAGS) -o $@ $<

test_pokedex_dex_num_buffer: test_pokedex_dex_num_buffer.c
	$(CC) $(CFLAGS) -o $@ $<

test: test_string_copy_padded test_pokedex_dex_num_buffer
	./test_string_copy_padded
	./test_pokedex_dex_num_buffer

clean:
	rm -f test_string_copy_padded test_pokedex_dex_num_buffer

.PHONY: test clean
