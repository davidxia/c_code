#include <stdio.h>

#include "sort.h"


int main() {
    int data[] = {0, 4, 1, 3, 1, 2, 4, 1};
    int size = 8;
    int k = 5;
    int i;

    printf("unsorted data:\n");
    for (i = 0; i < size; i++)
        printf("%d\n", data[i]);

    ctsort(data, size, k);

    printf("\nsorted data:\n");
    for (i = 0; i < size; i++)
        printf("%d\n", data[i]);

    return 0;
}

