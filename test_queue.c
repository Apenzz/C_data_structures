#include <stdio.h>
#include "queue.h"

int main() {
    QUEUE(int) my_int_queue;
    queue_init(my_int_queue, int);
    queue_enqueue(my_int_queue, 10);
    queue_enqueue(my_int_queue, 20);
    queue_enqueue(my_int_queue, 30);

    // check size
    printf("Size: %zu\n", queue_size(my_int_queue));

    // dequeue values
    int val;
    while(!queue_is_empty(my_int_queue)) {
        queue_dequeue(my_int_queue, &val);
        printf("Dequeued: %d\n", val);
    }

    queue_destroy(my_int_queue);
    return 0;
}
