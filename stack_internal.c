#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack_internal.h"

stack_internal *stack_internal_new(size_t element_size, size_t initial_cap) {
    stack_internal *s = malloc(sizeof(*s));
    if (!s) return NULL;
    s->data = malloc(element_size * initial_cap);
    if (!(s->data)) {
        free(s);
        return NULL;
    }
    s->element_size = element_size;
    s->capacity = (initial_cap <= 0) ? 1 : initial_cap;
    s->top = 0;
    return s;
}

bool stack_internal_pop(stack_internal *s, void *elem) {
    if (!s || !elem || stack_internal_is_empty(s)) return false;
    s->top--;
    void *source = (char *)s->data + (s->top * s->element_size); 
    memcpy(elem, source, s->element_size);
    return true;
}

bool stack_internal_peek(stack_internal *s, void *elem) {
    if (!s || !elem || stack_internal_is_empty(s)) return false;
    void *head = (char *)s->data + (s->element_size * (s->top - 1));
    memcpy(elem, head, s->element_size);
    return true;
}

void stack_internal_push(stack_internal *s, const void *elem) {
    if (!s || !elem) return;
    // resize stack_internal if size too small to add new entry
    if (s->capacity <= s->top) {
        void *new_data = realloc(s->data, (s->capacity * 2) * s->element_size);
        if (!new_data) {
            fprintf(stderr, "Could not resize stack_internal: realloc failed\n");
            return;
        } 
        s->data = new_data; 
        s->capacity *= 2;
    }
    void *target = (char *)s->data + (s->top * s->element_size);
    memcpy(target, elem, s->element_size);
    s->top++;
}

bool stack_internal_is_empty(stack_internal *s) {
    if (!s) return true;
    return (!(s->top));
}

size_t stack_internal_size(stack_internal *s) {
    if (!s) return 0;
    return s->top;
}

void stack_internal_free(stack_internal *s) {
    free(s->data);
    free(s); 
}

void stack_internal_clear(stack_internal *s) {
    if (!s) return;
    s->top = 0;
}
