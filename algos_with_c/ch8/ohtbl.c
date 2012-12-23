#include <stdlib.h>
#include <string.h>
#include "ohtbl.h"


/* Reserve a sentinel memory address for vacated elements. */
static char vacated;
int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *key), int (*h2)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data)) {
    int i;

    /* Allocate space for hash table */
    if ((htbl->table = (void **) malloc(positions * sizeof(void *))) == NULL)
        return -1;

    /* Initialize each position */
    htbl->positions = positions;
    for (i = 0; i < htbl->positions; i++)
        htbl->table[i] = NULL;

    /* Set the vacated member to the sentinel memory address reserved for this */
    htbl->vacated = &vacated;

    /* Encapsulate the functions */
    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destroy = destroy;

    /* Initialize the number of elements in the table */
    htbl->size = 0;
    return 0;
}


void ohtbl_destroy(OHTbl *htbl) {
    int i;

    if (htbl->destroy != NULL) {
        /* Call user-defined function to free dynamically allocated data. */
        for (i = 0; i < htbl->positions; i++) {
            if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
                htbl->destroy(htbl->table[i]);
        }
    }

    /* Free the storage allocated for the hash table */
    free(htbl->table);
    memset(htbl, 0, sizeof(OHTbl));
    return;
}


int ohtbl_insert(OHTbl *htbl, const void *data) {
    void *temp;
    int position, i;

    /* Don't exceed number of positions in table */
    if (htbl->size == htbl->positions)
        return -1;

    /* Do nothing if data is already in table */
    temp = (void *) data;
    if (ohtbl_lookup(htbl, &temp) == 0)
        return 1;

    /* Use double hashing to hash the key */
    for (i = 0; i < htbl->positions; i++) {
        position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
        if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated) {
            htbl->table[position] = (void *) data;
            htbl->size++;
            return 0;
        }
    }

    /* Return that the hash functions were selected incorrectly */
    return -1;
}


int ohtbl_remove(OHTbl *htbl, void **data) {
    int position, i;

    /* Use double hashing to hash the key */
    for (i = 0; i < htbl->positions; i++) {
        position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

        if (htbl->table[position] == NULL) {
            /* Return that data wasn't found */
            return -1;
        } else if (htbl->table[position] == htbl->vacated) {
            /* Search beyond vacated positions */
            continue;
        } else if (htbl->match(htbl->table[position], *data)) {
            /* Pass back the data from the table */
            *data = htbl->table[position];
            htbl->table[position] = htbl->vacated;
            htbl->size--;
            return 0;
        }
    }

    /* Return that data wasn't found */
    return -1;
}


int ohtbl_lookup(const OHTbl *htbl, void **data) {
    int position, i;

    for (i = 0; i < htbl->positions; i++) {
        position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

        if (htbl->table[position] == NULL) {
            return -1;
        } else if (htbl->match(htbl->table[position], *data)) {
            *data = htbl->table[position];
            return 0;
        }
    }

    return -1;
}

