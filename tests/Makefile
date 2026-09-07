CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0

LN_SRC = ../src/lnet/lnet_net.c ../src/lnet/lnet_session.c ../src/lnet/lnet_sio.c
LN_INC = -I../src/lnet

test_string_copy_padded: test_string_copy_padded.c
	$(CC) $(CFLAGS) -o $@ $<

test_pokedex_dex_num_buffer: test_pokedex_dex_num_buffer.c
	$(CC) $(CFLAGS) -o $@ $<

test_lnet_session: test_lnet_session.c $(LN_SRC)
	$(CC) $(CFLAGS) $(LN_INC) -o $@ $< $(LN_SRC) -lpthread

test: test_string_copy_padded test_pokedex_dex_num_buffer test_lnet_session
	./test_string_copy_padded
	./test_pokedex_dex_num_buffer
	./test_lnet_session

clean:
	rm -f test_string_copy_padded test_pokedex_dex_num_buffer test_lnet_session

.PHONY: test clean