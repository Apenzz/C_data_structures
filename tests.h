#ifndef __TESTS_H__
#define __TESTS_H__

#define TEST_START(name) printf("Running test: %s... ", name)
#define TEST_END() printf("PASSED\n")
#define ASSERT(exp, msg) if (!(exp)) { printf("\nFAIL: %s\n", msg); return; }

typedef struct {
    int id;
    char name[20];
} _Test_Person;

/* queue testing functions */
void test_basic_int_queue();
void test_struct_handling_queue();
void test_wrap_around_and_resize_queue();
void test_empty_peek_queue();

/* stack testing functions */
void test_basic_int_stack();
void test_struct_handling_stack();
void test_empty_peek_stack();

#endif
