#include <stdio.h>
#include <assert.h>

#include "stack.h"

void test_size_empty() {
    Stack s = stack_new(sizeof(int), 10);
    assert(stack_size(s) == 0); 
    assert(stack_is_empty(s));
}

void test_size_null_stack() {
    Stack s = NULL;
    assert(stack_size(s) == 0);
    assert(stack_is_empty(s));
}

void test_pop_stack_empty() {
    Stack s = stack_new(sizeof(int), 10);
    void *elem;
    stack_pop(s, elem);
    assert(!elem);
}

int main() {
    test_size_empty();
    test_size_null_stack();
    return 0;
}
