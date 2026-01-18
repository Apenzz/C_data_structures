#ifndef __QUEUE_INTERNAL_H__
#define __QUEUE_INTERNAL_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t capacity;
    size_t count;
    size_t front;
    size_t back;
} queue_internal;


queue_internal *queue_internal_new(size_t element_size);

void queue_internal_destroy(queue_internal *q);

bool queue_internal_enqueue(queue_internal *q, const void *element);

bool queue_internal_dequeue(queue_internal *q, void *element);

bool queue_internal_peek(queue_internal *q, void *element);

bool queue_internal_is_empty(queue_internal *q);

size_t queue_internal_size(queue_internal *q);

#endif
