#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct Stack {
    void *data; // pointer to beginning of stack area
    size_t element_size; // size of one element in bytes
    size_t capacity; // max number of elements that can fit in currect stack before resizing
    size_t top; // index of current 'top' element | number of elements in the stack
};

struct Stack *stack_new(size_t element_size, size_t initial_cap) {
    struct Stack *s = malloc(sizeof(*s));
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

bool stack_pop(struct Stack *s, void *elem) {
    if (!s || !elem || stack_is_empty(s)) return false;
    s->top--;
    void *source = (char *)s->data + (s->top * s->element_size); 
    memcpy(elem, source, s->element_size);
    return true;
}

bool stack_peek(struct Stack *s, void *elem) {
    if (!s || !elem || stack_is_empty(s)) return false;
    void *head = (char *)s->data + (s->element_size * (s->top - 1));
    memcpy(elem, head, s->element_size);
    return true;
}

void stack_push(struct Stack *s, const void *elem) {
    if (!s || !elem) return;
    // resize stack if size too small to add new entry
    if (s->capacity <= s->top) {
        void *new_data = realloc(s->data, (s->capacity * 2) * s->element_size);
        if (!new_data) {
            fprintf(stderr, "Could not resize stack: realloc failed\n");
            return;
        } 
        s->data = new_data; 
        s->capacity *= 2;
    }
    void *target = (char *)s->data + (s->top * s->element_size);
    memcpy(target, elem, s->element_size);
    s->top++;
}

bool stack_is_empty(struct Stack *s) {
    if (!s) return true;
    return (!(s->top));
}

size_t stack_size(struct Stack *s) {
    if (!s) return 0;
    return s->top;
}

void stack_free(struct Stack *s) {
    free(s->data);
    free(s); 
}

void stack_clear(struct Stack *s) {
    if (!s) return;
    s->top = 0;
}
