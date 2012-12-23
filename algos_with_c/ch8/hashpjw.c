#include <stdio.h>
/* #include "hashpjw.h" */


unsigned int hashpjw(const void *key) {
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

    return val % 1699;
}


int main() {
    char *str = "hi";
    printf("%d\n", hashpjw(str));
}
