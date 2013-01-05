#include <stdio.h>

#include "sort.h"


int main() {
    int data[] = {302, 253, 611, 901, 529, 102};
    int size = 6;
    int p = 3, k = 10;
    int i;

    printf("unsorted data:\n");
    for (i = 0; i < size; i++)
        printf("%d\n", data[i]);

    rxsort(data, size, p, k);

    printf("\nsorted data:\n");
    for (i = 0; i < size; i++)
        printf("%d\n", data[i]);

    return 0;
}

