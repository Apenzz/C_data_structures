#include "tests.h"

int main() {
    test_basic_int_queue();
    test_struct_handling_queue();
    test_wrap_around_and_resize_queue();
    test_empty_peek_queue();
    test_basic_int_stack();
    test_struct_handling_stack();
    test_empty_peek_stack();
    return 0;
}
