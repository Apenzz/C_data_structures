#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "queue_internal.h"

#define QUEUE(type) \
    struct { \
        queue_internal *_internal; \
        type *_type_check; \
    }

#define queue_init(queue, type) \
    do { \
        (queue)._internal = queue_internal_new(sizeof(type)); \
        (queue)._type_check = NULL; \
    } while(0)

#define queue_destroy(queue) \
    queue_internal_destroy((queue)._internal)

#define queue_enqueue(queue, element) \
    do { \
        __typeof__(*(queue._type_check)) _elem = (element); \
        queue_internal_enqueue((queue)._internal, &_elem); \
    } while(0)

#define queue_dequeue(queue, element) \
    do { \
        __typeof__(*(queue._type_check)) _elem = (element); \
        queue_internal_dequeue((queue)._internal, & elem); \
    } while(0)

#define queue_peek(queue, element) \
    do { \
       __typeof__(*(queue._type_check)) _elem = (element); \
       queue_internal_peek((queue)._internal, &elem); \
    } while(0) 

#define queue_is_empty(queue) \
    do { \
        queue_internal_is_empty((queue)._internal) \
    } while(0) 

#define queue_size(queue) \
    do { \
        queue_internal_size((queue)._internal) \
    } while(0)

#endif
