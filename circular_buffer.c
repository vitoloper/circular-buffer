/*
 * Circular buffer library.
 * 
 * Copyright (c) 2025 vitoloper
 * 
 */

#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/* Allocate circular buffer. */
struct Circbuf *circbuf_alloc(size_t size) {
    /* Allocate space for struct */
    struct Circbuf *cb = (struct Circbuf *)malloc(sizeof(struct Circbuf));
    
    /* Allocate space for buffer and set indices and size. */
    cb->buf = (char *)malloc(sizeof(char) * size);
    cb->write_idx = 0;
    cb->read_idx = 0;
    cb->size = size;

    return cb;
}

/* Free allocated memory. */
void circbuf_free(struct Circbuf *cb) {
    free(cb->buf);
    free(cb);
}

/* Insert (push) an element. */
size_t circbuf_push(struct Circbuf *cb, char data) {
    /* Check if buffer is full. */
    if ((cb->write_idx + 1) % (cb->size) == cb->read_idx) {
        return 0;
    }

    /* Write data */
    cb->buf[cb->write_idx] = data;

    /* Increment write_idx */
    cb->write_idx = (cb->write_idx + 1) % cb->size;

    return 1;
}

/* Read (pop) an element. */
size_t circbuf_pop(struct Circbuf *cb, char *data) {
    /* Check if buffer is empty. */
    if(cb->read_idx == cb->write_idx) {
        return 0;
    }

    /* Read data */
    *data = cb->buf[cb->read_idx];

    /* Increment read_idx */
    cb->read_idx = (cb->read_idx + 1) % cb->size;

    return 1;
}

/* Push n elements from src linear array to cb. */
size_t circbuf_push_from_linear(struct Circbuf *cb, char *src, size_t n) {
    size_t i;

    for (i = 0; i < n && i < cb->size-1; i++) {
        /* Push element and check if successful. */
        if (circbuf_push(cb, src[i]) == 0) return i;
    }

    /* Return the number of elements. */
    return i;
}

/* Pop n elements from cb to dest linear array. */
size_t circbuf_pop_to_linear(char *dest, struct Circbuf *cb, size_t n) {
    size_t i;

    for(i = 0; i < n; i++) {
        /* Pop element and check if successful. */
        if (circbuf_pop(cb, &dest[i]) == 0) return i;
    }

    /* Return the number of elements. */
    return i;
}

/* Copy n elements from cb to dest (copy at most circbuf_len() elements). */
size_t circbuf_copy_to_linear(char *dest, struct Circbuf *cb, size_t n) {
    size_t i;
    size_t len = circbuf_len(cb);
    size_t read_idx = cb->read_idx;

    for (i = 0; i < n && i < len; i++) {
        /* Read data and increment read_idx. */
        dest[i] = cb->buf[read_idx];
        read_idx = (read_idx + 1) % cb->size;
    }

    /* Return the number of copied elements. */
    return i;
}

/* Empty buffer. */
void circbuf_empty(struct Circbuf *cb) {
    cb->read_idx = cb->write_idx;
}

/* Get buffer length (number of stored elements). */
size_t circbuf_len(struct Circbuf * cb) {
    if (cb->write_idx == cb->read_idx) {
        return 0;
    } else if (cb->write_idx > cb->read_idx) {
        return cb->write_idx - cb->read_idx;
    } else {
        return cb->write_idx - cb->read_idx + cb->size;   
    }
}

/* Get buffer size. */
size_t circbuf_size(struct Circbuf *cb) {
    return cb->size;
}

/* Get buffer remaining space. */
size_t circbuf_space_left(struct Circbuf *cb) {
    return cb->size - 1 - circbuf_len(cb);
}

/* Print buffer data, indices and size. */
void circbuf_print_data(struct Circbuf *cb) {
    size_t i;
    size_t cb_len = circbuf_len(cb);
    size_t read_idx = cb->read_idx;

    printf("write_idx: %lu\n",cb->write_idx);
    printf("read_idx: %lu\n", cb->read_idx);
    printf("length: %lu\n", cb_len);
    printf("size: %lu\n", cb->size);

    printf("Data: ");
    if (cb_len == 0) {
        printf("(empty)");
    } else {
        for (i = 0; i < cb_len; i++) {
            printf("%c ", cb->buf[read_idx]);
            read_idx = (read_idx + 1) % cb->size;
        };
    }

    printf("\n");
}