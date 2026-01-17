#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue_internal.h"

queue_internal *queue_internal_new(size_t element_size) {
    queue_internal *q = malloc(sizeof(*q));
    if (!q) return NULL;
    q->capacity = 1;
    q->data = malloc(element_size * q->capacity);
    if (!(q->data)) {
        free(q);
        return NULL;
    } 
    q->element_size = element_size;
    q->front = 0;
    q->back = 0;
    q->count = 0;
    return q;
}

void queue_internal_destroy(queue_internal *q) {
    if (!q) return;
    free(q->data);
    free(q);
}

void queue_internal_enqueue(queue_internal *q, const void *elem) {
    if (!q || !elem) return;
    // check if enough space in the queue
    if (q->capacity <= q->count) {
        size_t old_capacity = q->capacity;
        size_t new_capacity = old_capacity * 2;
        void *new_data = realloc(q->data, q->element_size * new_capacity);
        if (!new_data) {
            fprintf(stderr, "Couldn't not resize queue: realloc failed\n");
            return;
        }
        q->data = new_data;
        // if the queue has wrapped around , we need to unwrap it
        if (q->back <= q->front && q->count > 0) {
            size_t elements_at_end = old_capacity - q->front; 
            memmove((char *)q->data + ((new_capacity - elements_at_end) * q->element_size), (char *)q->data + (q->front * q->element_size), elements_at_end * q->element_size);
            q->front = new_capacity - elements_at_end;
        }
        q->capacity = new_capacity;
    }
    void *next = (char *)q->data + (q->element_size * q->back);
    memcpy(next, elem, q->element_size);
    q->back = (q->back + 1) % q->capacity;
    q->count++;
}

bool queue_internal_dequeue(queue_internal *q, void *elem) {
    if (!q || !elem) return false;
    if (queue_internal_is_empty(q)) return false; 
    void *target = (char *)q->data + (q->element_size * q->front);
    memcpy(elem, target, q->element_size);
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    return true;
}

bool queue_internal_peek(queue_internal *q, void *elem) {
    if (!q || !elem) return false;
    if (queue_internal_is_empty(q)) return false; 
    void *target = (char *)q->data + (q->element_size * q->front);
    memcpy(elem, target, q->element_size);
    return true;
}
 
bool queue_internal_is_empty(queue_internal *q) {
    if (!q) return false;
    return !(q->count);
}

size_t queue_internal_size(queue_internal *q) {
    return q->count;
}
