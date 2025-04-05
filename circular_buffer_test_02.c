/*
 * Circular buffer testing (02).
 *
 */

#include "circular_buffer.h"
#include <stdio.h>
#include <assert.h>

int main() {
    struct Circbuf *cb = circbuf_alloc(6);
    char *str = "Thequickbrownfoxjumpsoverthelazydog";

    printf("Initial status\n");
    circbuf_print_data(cb);

    printf("\nPush data (5 elements should be pushed)\n");
    assert(circbuf_push_from_linear(cb, str, sizeof(str)) == cb->size - 1);
    
    circbuf_print_data(cb);

    printf("\nEmpty buffer\n");
    circbuf_empty(cb);
    assert(circbuf_len(cb) == 0);

    circbuf_print_data(cb);

    printf("\nPush data (3 elements should be pushed)\n");
    assert(circbuf_push_from_linear(cb, str, 3) == 3);

    circbuf_print_data(cb);

    printf("\nSpace left: %d\n", circbuf_space_left(cb));

    printf("\nPush data (2 elements should be pushed)\n");
    assert(circbuf_push_from_linear(cb, str+8, 8) == 2);

    circbuf_print_data(cb);

    printf("\nSpace left: %d\n", circbuf_space_left(cb));
    
    circbuf_free(cb);
    return 0;
}