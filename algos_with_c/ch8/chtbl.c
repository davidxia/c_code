#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../ch5/list.h"
#include "../ch5/list.c"
#include "chtbl.h"

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data)) {
    int i;

    if ((htbl->table = (List *) malloc(buckets * sizeof(List))) == NULL)
        return -1;

    /* Initialize buckets */
    htbl->buckets = buckets;
    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    /* Encapsulate the functions */
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;

    htbl->size = 0;
    return 0;
}


void chtbl_destroy(CHTbl *htbl) {
    int i;
    for (i = 0; i < htbl->buckets; i++) {
        list_destroy(&htbl->table[i]);
    }

    /* Free the storage allocated for the hash table */
    free(htbl->table);

    /* Clear the structure as precaution */
    memset(htbl, 0, sizeof(CHTbl));
    return;
}


int chtbl_insert(CHTbl *htbl, const void *data) {
    void *temp;
    int bucket, retval;

    /* Do nothing if data already in table */
    temp = (void *) data;
    if (chtbl_lookup(htbl, &temp) == 0)
        return -1;

    bucket = htbl->h(data) % htbl->buckets;

    /* Insert data into bucket */
    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;

    return retval;
}


int chtbl_remove(CHTbl *htbl, void **data) {
    ListElmt *element, *prev;
    int bucket;

    bucket = htbl->h(*data) % htbl->buckets;

    /* Search for data in the bucket */
    prev = NULL;
    for (element = list_head(&htbl->table[bucket]); element != NULL;
         element = list_next(element)) {
        if (htbl->match(*data, list_data(element))) {
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                htbl->size--;
                return 0;
            } else {
                return -1;
            }
        }

        prev = element;
    }

    /* Return that the data wasn't found */
    return -1;
}


int chtbl_lookup(const CHTbl *htbl, void **data) {
    ListElmt *element;
    int bucket;

    bucket = htbl->h(*data) % htbl->buckets;

    /* Search for data in bucket */
    for (element = list_head(&htbl->table[bucket]); element != NULL;
         element = list_next(element)) {
        if (htbl->match(*data, list_data(element))) {
            /* Pass back data from table */
            *data = list_data(element);
            return 0;
        }
    }

    /* Return that data wasn't found */
    return -1;
}


int hash_func(const void *key) {
    const char *ptr;
    unsigned int val;

    /* Hash the key by performing a number of bit operations on it. */
    val = 0;
    ptr = key;

    while (*ptr != '\0') {
        unsigned int tmp;
        val = (val << 4) + (*ptr);

        if (tmp = (val & 0xf0000000)) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }

        ptr++;
    }

    return val;
}


int mystrcmp(const void *str1, const void *str2) {
    if (strcmp((const char *) str1, (const char *) str2) == 0) {
        return 1;
    }
    return 0;
}


int main() {
    CHTbl htbl;
    char *str = "hi there";
    char *str2 = "hi";
    char *str3 = "hi there";
    chtbl_init(&htbl, 5, hash_func, mystrcmp, free);

    if (chtbl_insert(&htbl, str) != 0)
        return -1;

    if (chtbl_lookup(&htbl, (void **) &str2) == 0)
        printf("FOUND str2\n");

    if (chtbl_lookup(&htbl, (void **) &str3) == 0)
        printf("FOUND str3\n");

    return 0;
}

