all: circular_buffer_test_01 circular_buffer_test_02
CFLAGS=-O2 -Wall

circular_buffer_test_01: circular_buffer_test_01.c circular_buffer.c
	$(CC) circular_buffer_test_01.c circular_buffer.c -o circular_buffer_test_01 $(CFLAGS)

circular_buffer_test_02: circular_buffer_test_02.c circular_buffer.c
	$(CC) circular_buffer_test_02.c circular_buffer.c -o circular_buffer_test_02 $(CFLAGS)

clean:
	rm -f circular_buffer_test_01 circular_buffer_test_02