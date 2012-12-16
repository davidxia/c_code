#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "list.c"
#include "queue.h"


int queue_enqueue(Queue *queue, const void *data) {
    return list_ins_next(queue, list_tail(queue), data);
}


int queue_dequeue(Queue *queue, void **data) {
    return list_rem_next(queue, NULL, data);
}


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

