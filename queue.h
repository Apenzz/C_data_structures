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

#define queue_enqueue(queue, element) ({ \
    __typeof__(*((queue)._type_check)) _q_tmp = (element); \
    queue_internal_enqueue((queue)._internal, &(_q_tmp)); \
})

#define queue_dequeue(queue, element_ptr) \
    queue_internal_dequeue((queue)._internal, (element_ptr))

#define queue_peek(queue, element_ptr) \
   queue_internal_peek((queue)._internal, (element_ptr))

#define queue_is_empty(queue) \
    queue_internal_is_empty((queue)._internal)

#define queue_size(queue) \
    queue_internal_size((queue)._internal)

#endif
