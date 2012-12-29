#include <stdio.h>
#include "heap.h"


int cmp(int *key1, int *key2) {
    if (*key1 > *key2)
        return 1;
    else if (*key1 < *key2)
        return -1;
    else
        return 0;
}


int main() {
    Heap heap;
    heap_init(&heap, (int (*)(const void *, const void *)) cmp, NULL);

    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int *data6 = NULL;

    heap_insert(&heap, &data1);
    heap_insert(&heap, &data2);
    heap_insert(&heap, &data3);
    heap_insert(&heap, &data4);
    heap_insert(&heap, &data5);

    int i;
    for (i = heap_size(&heap); i > 0; i--) {
        if (heap_extract(&heap, (void **) &data6) == 0)
            printf("%d\n", *data6);
    }

    return 0;
}
