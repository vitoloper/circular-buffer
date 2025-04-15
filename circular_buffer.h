/*
 * Circular buffer library header file.
 * 
 * Copyright (c) 2025 vitoloper
 * 
 */

#ifndef CIRCBUFLIB_H
#define CIRCBUFLIB_H

#include <stddef.h>

struct Circbuf {
    char *buf;
    size_t write_idx;
    size_t read_idx;
    size_t size;   // if size is N, actual capacity is N-1
};

struct Circbuf *circbuf_alloc(size_t len);
void circbuf_free(struct Circbuf *cb);
size_t circbuf_push(struct Circbuf *cb, char data);
size_t circbuf_pop(struct Circbuf *cb, char *data);
size_t circbuf_push_from_linear(struct Circbuf *cb, char *src, size_t n);
size_t circbuf_pop_to_linear(char *dest, struct Circbuf *cb, size_t n);
size_t circbuf_copy_to_linear(char *dest, struct Circbuf *cb, size_t n);
void circbuf_empty(struct Circbuf *cb);
size_t circbuf_len(struct Circbuf * cb);
size_t circbuf_size(struct Circbuf *cb);
size_t circbuf_space_left(struct Circbuf *cb);
void circbuf_print_data(struct Circbuf *cb);

#endif // CIRCBUFLIB_H