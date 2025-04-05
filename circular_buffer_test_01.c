/*
 * Circular buffer testing (01).
 *
 */

#include "circular_buffer.h"
#include <stdio.h>
#include <assert.h>

int main() {
    char data;
    struct Circbuf *cb = circbuf_alloc(5);

    printf("Initial status\n");
    circbuf_print_data(cb);

    printf("\nPush 5 elements (4 successful pushes expected)\n");
    assert(circbuf_push(cb, 'T') == 1);
    assert(circbuf_push(cb, 'e') == 1);
    assert(circbuf_push(cb, 's') == 1);
    assert(circbuf_push(cb, 't') == 1);
    assert(circbuf_push(cb, '!') == 0);

    circbuf_print_data(cb);

    printf("\nPop 5 elements (4 successful pops expected)\n");
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == 'T');
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == 'e');
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == 's');
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == 't');
    assert(circbuf_pop(cb, &data) == 0);

    circbuf_print_data(cb);

    printf("\nPush 3 elements\n");
    assert(circbuf_push(cb, '1') == 1);
    assert(circbuf_push(cb, '2') == 1);
    assert(circbuf_push(cb, '3') == 1);

    circbuf_print_data(cb);

    printf("\nPop 3 elements\n");
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == '1');
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == '2');
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == '3');

    circbuf_print_data(cb);

    printf("\nPush 2 elements\n");
    assert(circbuf_push(cb, 'A') == 1);
    assert(circbuf_push(cb, 'B') == 1);

    circbuf_print_data(cb);

    printf("\nPop 1 element\n");
    assert(circbuf_pop(cb, &data) == 1);
    assert(data == 'A');

    circbuf_print_data(cb);

    circbuf_free(cb);
    return 0;
}