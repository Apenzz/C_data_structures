#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "stack.h"
#include "tests.h"

void test_basic_int_stack() {
    TEST_START("BASIC INTEGER LIFO");
    STACK(int) s; 
    stack_init(s, int, 1);
    
    int val;
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);

    ASSERT(stack_size(s) == 3, "Size should be 3");

    stack_pop(s, &val);
    ASSERT(val == 30, "First out should be 30");
    stack_pop(s, &val);
    ASSERT(val == 20, "Second out should be 20");
    
    stack_destroy(s);
    TEST_END();
}

void test_struct_handling_stack() {
    TEST_START("Generic struct handling");
    STACK(_Test_Person) s;
    stack_init(s, _Test_Person, 1);

    _Test_Person p1 = {1, "Alice"};
    _Test_Person p2 = {2, "Bob"};
    stack_push(s, p1);
    stack_push(s, p2);

    _Test_Person out;
    stack_pop(s, &out);
    ASSERT(out.id == 2 && strcmp(out.name, "Bob") == 0, "Struct data mismatch");

    stack_destroy(s);
    TEST_END();
}

void test_empty_peek_stack() {
    TEST_START("Empty and peek operations");
    STACK(double) s;
    stack_init(s, double, 1);

    double d;
    ASSERT(stack_is_empty(s) == true, "Queue should be empty");
    ASSERT(stack_pop(s, &d) == false, "Dequeing an empty buffer should return false");

    stack_push(s, 3.14);
    ASSERT(stack_peek(s, &d) == true, "Peeking should succeed");
    ASSERT(d == 3.14, "Peek value mismatch");
    ASSERT(stack_size(s) == 1, "Size should still be one after peeking");

    stack_destroy(s);
    TEST_END();
}
