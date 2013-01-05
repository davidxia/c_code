#include <stdio.h>
#include <string.h>

#include "search.h"


int intcmp(int *x, int *y) {
    printf("*x = %c, *x = %d\n", *x, *x);
    printf("*y = %c, *y = %d\n", *y, *y);
    if (*x > *y)
        return 1;
    else if (*x < *y)
        return -1;
    else
        return 0;
}


int main() {
    char data[5] = {'a', 'b', 'c', 'd', 'e'};
    char target = 'd';
    int size = 5;
    int esize = 1;

    int i = bisearch(data, &target, size, esize,
                     (int (*)(const void *, const void *)) intcmp);
    printf("%d\n", i);
    return 0;
}

