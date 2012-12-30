#include <stdio.h>

#include "queue.h"


int main() {
    Queue queue;
    queue_init(&queue, free);

    int *data;
    int data1;
    data1 = 4;
    int data2;
    data2 = 9;
    queue_enqueue(&queue, &data1);
    queue_enqueue(&queue, &data2);
    printf("%d\n", queue_size(&queue));

    while (queue_size(&queue) > 0) {
        queue_dequeue(&queue, (void *) &data);
        printf("queue_dequeue returned %d\n", *data);
    }

    return 0;
}


