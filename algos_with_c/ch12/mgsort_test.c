#include <stdio.h>

#include "sort.h"


int intcmp(int *x, int *y) {
    if (*x > *y)
        return 1;
    else if (*x < *y)
        return -1;
    else
        return 0;
}


int main() {
    int i, data_len = 8;
    int data[] = {82, 70, 11, 72, 25, 36, 44, 10};

    printf("unsorted array:\n");
    for (i = 0; i < data_len; i++) {
        printf("%d\n", data[i]);
    }

    mgsort(data, data_len, sizeof(int), 0, data_len - 1, (int (*)(const void *, const void *)) intcmp);

    printf("\nsorted array:\n");
    for (i = 0; i < data_len; i++) {
        printf("%d\n", data[i]);
    }

    return 0;
}

