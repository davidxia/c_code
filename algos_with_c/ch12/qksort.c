#include <stdlib.h>
#include <string.h>

#include "sort.h"


static int compare_int(const void *int1, const void *int2) {
    /* Compare two integers (used during median-of-three partitioning */
    if (*(const int *) int1 > *(const int *) int2)
        return 1;
    else if (*(const int *) int1 < *(const int *) int2)
        return -1;
    else
        return 0;
}


static int partition(void *data, int esize, int i, int k,
                     int (*compare)(const void *key1, const void *key2)) {
    char *a = data;
    void *pval, *temp;
    int r[3];

    /* Allocate storage for the partition value and swapping */
    if ((pval = malloc(esize)) == NULL)
        return -1;
    if ((temp = malloc(esize)) == NULL) {
        free(pval);
        return -1;
    }

    /* Use median-of-three method to find partition value */
    r[0] = (rand() % (k - i + 1)) + i;
    r[1] = (rand() % (k - i + 1)) + i;
    r[2] = (rand() % (k - i + 1)) + i;
    issort(r, 3, sizeof(int), compare_int);
    memcpy(pval, &a[r[1] * esize], esize);

    /* Create two partitions around the partition value */
    i--;
    k++;

    while (1) {
        /* Move left until an element is found in the wrong partition */
        do {
           k--;
        } while (compare(&a[k * esize], pval) > 0);

        /* Move right until an element is found in the wrong partition */
        do {
            i++;
        } while (compare(&a[i * esize], pval) < 0);

        if (i >= k) {
            /* Stop partitioning when the left and right counters cross */
            break;
        } else {
            /* Swap the elements now under the left and right counters */
            memcpy(temp, &a[i * esize], esize);
            memcpy(&a[i * esize], &a[k * esize], esize);
            memcpy(&a[k * esize], temp, esize);
        }
    }

    /* Free storage allocated for partitioning */
    free(pval);
    free(temp);

    /* Return the position dividing the two partitions */
    return k;
}


int qksort(void *data, int size, int esize, int i, int k,
           int (*compare)(const void *key1, const void *key2)) {
    int j;

    /* Stop recursion when it's not possible to partition further */
    while (i < k) {
        /* Determine where to partition the elements */
        if ((j = partition(data, esize, i, k, compare)) < 0)
            return -1;

        /* Recursively sort the left partition */
        if (qksort(data, size, esize, i, j, compare) < 0)
            return -1;

        /* Iterate and sort right partition */
        i = j + 1;
    }

    return 0;
}

