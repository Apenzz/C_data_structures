#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack *Stack;

Stack stack_new(size_t element_size, size_t initial_cap);

void stack_free(Stack s);

bool stack_pop(Stack s, void *elem);

void stack_push(Stack s, const void *elem);

bool stack_peek(Stack s, void *elem);

bool stack_is_empty(Stack s);

size_t stack_size(Stack s);

void stack_clear(Stack s);

#endif
