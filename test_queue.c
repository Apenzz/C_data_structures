#include "queue.h"

int main() {
    QUEUE(int) my_int_queue;
    queue_init(my_int_queue, int);
    queue_enqueue(my_int_queue, 10);
    queue_enqueue(my_int_queue, 20);
    queue_enqueue(my_int_queue, 30);


    return 0;
}
