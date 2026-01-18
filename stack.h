#ifndef __STACK_H__
#define __STACK_H__

#include "stack_internal.h"

#define STACK(type) \
    struct { \
        stack_internal *_internal; \
        type *_type_check; \
    }

#define stack_init(stack, type, init_cap) \
    do { \
        (stack)._internal = stack_internal_new(sizeof(type), (init_cap)); \
        (stack)._type_check = NULL; \
    } while(0)

#define stack_destroy(stack) \
    stack_internal_free((stack)._internal) \

#define stack_pop(stack, element_ptr) \
    stack_internal_pop((stack)._internal, (element_ptr)) 

#define stack_push(stack, element) ({ \
    __typeof__(*(stack)._type_check) _s_tmp = (element); \
    stack_internal_push((stack)._internal, &(_s_tmp)); \
})

#define stack_peek(stack, element_ptr) \
    stack_internal_peek((stack)._internal, (element_ptr))

#define stack_is_empty(stack) \
    stack_internal_is_empty((stack)._internal)

#define stack_size(stack) \
    stack_internal_size((stack)._internal)

#define stack_clear(stack) \
    stack_internal_clear((stack)._internal)

#endif
