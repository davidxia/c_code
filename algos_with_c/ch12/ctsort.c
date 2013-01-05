#include <stdlib.h>
#include <string.h>

#include "sort.h"


int ctsort(int *data, int size, int k) {
    int *counts, *temp;
    int i, j;

    /* Allocate storage for the counts */
    if ((counts = (int *) malloc(k * sizeof(int))) == NULL)
        return -1;

    /* Allocate storage for sorted elements */
    if ((temp = (int *) malloc(size * sizeof(int))) == NULL) {
        free(counts);
        return -1;
    }

    /* Initialize the counts */
    for (i = 0; i < k; i++)
        counts[i] = 0;

    /* Count occurrences of each element */
    for (j = 0; j < size; j++)
        counts[data[j]] = counts[data[j]]  + 1;

    /* Adjust each count to reflect counts before it */
    for (i = 1; i < k; i++)
        counts[i] = counts[i] + counts[i - 1];

    /* Use counts to position each element where it belongs */
    for (j = size - 1; j >= 0; j--) {
        temp[counts[data[j]] - 1] = data[j];
        counts[data[j]] = counts[data[j]] - 1;
    }

    /* Prepare to pass back sorted data */
    memcpy(data, temp, size * sizeof(int));

    /* Free storage allocated for sorting */
    free(counts);
    free(temp);
    return 0;
}

