#ifndef __STACK_INTERNAL_H__
#define __STACK_INTERNAL_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t capacity;
    size_t top;
} stack_internal;

stack_internal *stack_internal_new(size_t element_size, size_t initial_cap); // TODO: check that initial_cap logic is implemented

void stack_internal_free(stack_internal *s);

bool stack_internal_pop(stack_internal *s, void *elem);

void stack_internal_push(stack_internal *s, const void *elem);

bool stack_internal_peek(stack_internal *s, void *elem);

bool stack_internal_is_empty(stack_internal *s);

size_t stack_internal_size(stack_internal *s);

void stack_internal_clear(stack_internal *s);

#endif
