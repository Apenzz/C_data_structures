#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "queue.h"

#define TEST_START(name) printf("Running test: %s... ", name)
#define TEST_END() printf("PASSED\n")
#define ASSERT(exp, msg) if (!(exp)) { printf("\nFAIL: %s\n", msg); return; }

typedef struct {
    int id;
    char name[20];
} Person;

void test_basic_int() {
    TEST_START("BASIC INTEGER FIFO");
    QUEUE(int) q;
    queue_init(q, int); 

    int val;
    queue_enqueue(q, 10);
    queue_enqueue(q, 20);
    queue_enqueue(q, 30);

    ASSERT(queue_size(q) == 3, "Size should be 3");

    queue_dequeue(q, &val);
    ASSERT(val == 10, "First out should be 10");
    queue_dequeue(q, &val);
    ASSERT(val == 20, "Second out should be 20");

    queue_destroy(q);
    TEST_END();
}

void test_struct_handling() {
    TEST_START("Generic struct handling");
    QUEUE(Person) q;
    queue_init(q, Person);

    Person p1 = {1, "Alice"};
    Person p2 = {2, "Bob"};
    queue_enqueue(q, p1);
    queue_enqueue(q, p2);

    Person out;
    queue_dequeue(q, &out);
    ASSERT(out.id == 1 && strcmp(out.name, "Alice") == 0, "Struct data mismatch");

    queue_destroy(q);
    TEST_END();
}

void test_wrap_around_and_resize() {
    TEST_START("Circular wrap-around and dynamic resize");
    // initial capacity is 1
    QUEUE(int) q;
    queue_init(q, int);

    // Fill and force resize to cap 2
    queue_enqueue(q, 1);
    queue_enqueue(q, 2);

    // Dequeue 1 to move front to index 1
    int val;
    queue_dequeue(q, &val); // val=1, front=1
    
    // Enqueue '3' to wrap back to index 0
    queue_enqueue(q, 3); // back=0. Buffer looks like [3,2]
    
    // Force resize while wrapped
    // size is 2, cap is 2 -> trigger resize to 4
    queue_enqueue(q, 4);

    // Verify order: should be 2,3,4
    ASSERT(queue_size(q) == 3, "Queue should have size 3");
    queue_dequeue(q, &val); ASSERT(val == 2, "Value should be 2");
    queue_dequeue(q, &val); ASSERT(val == 3, "Value should be 3");
    queue_dequeue(q, &val); ASSERT(val == 4, "Value should be 4");
    ASSERT(queue_is_empty(q), "Queue should be empty");

    queue_destroy(q);
    TEST_END();
}

void test_empty_peek() {
    TEST_START("Empty and peek operations");
    QUEUE(double) q;
    queue_init(q, double);

    double d;
    ASSERT(queue_is_empty(q) == true, "Queue should be empty");
    ASSERT(queue_dequeue(q, &d) == false, "Dequeing an empty buffer should return false");

    queue_enqueue(q, 3.14);
    ASSERT(queue_peek(q, &d) == true, "Peeking should succeed");
    ASSERT(d == 3.14, "Peek value mismatch");
    ASSERT(queue_size(q) == 1, "Size should still be one after peeking");

    queue_destroy(q);
    TEST_END();
}

int main() {
    test_basic_int();
    test_struct_handling();
    test_wrap_around_and_resize();
    test_empty_peek();
    return 0;
}
