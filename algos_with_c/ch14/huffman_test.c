#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "compress.h"


int main() {
    unsigned char original[] = "hello world";
    unsigned char **compressed;
    unsigned char *original2;
    int size = strlen(original);
    int i, freq, r;

    r = huffman_compress(original, compressed, size);
    if (r == -1)
        return -1;
    printf("size of compressed = %d bytes\n", r);
    printf("size of original = %d bytes\n\n", **compressed);

    for (i = 0; i <= UCHAR_MAX; i++) {
        if ((freq = *(*compressed + sizeof(int) + i)) > 0) {
            printf("ascii value = %d, freq = %d\n", i, freq);
        }
    }

    printf("\nhex dump of compressed var's bytes\n");
    for (i = 0; i < 264; i++) {
        printf("%x ", *(*compressed + i));
    }
    printf("\n\n");

    if (huffman_uncompress(*compressed, &original2) == -1)
        return -1;
    printf("original was:\n");
    for (i = 0; i < size; i++) {
        printf("%c", *(original2 + i));
    }

    return 0;
}

