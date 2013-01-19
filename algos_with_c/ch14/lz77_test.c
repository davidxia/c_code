#include <stdio.h>
#include <string.h>

#include "bit.h"
#include "compress.h"


int main() {
    unsigned char original[] = "hello world";
    unsigned char *compressed, *original2;
    int size = strlen(original);
    int clength, i;

    clength = lz77_compress(original, &compressed, size);
    if (clength == -1)
        return -1;
    printf("size of compressed = %d bytes\n", clength);
    printf("size of original = %d bytes\n\n", *compressed);

    printf("\nhex dump of compressed var's bytes\n");
    for (i = 0; i < clength; i++) {
        printf("%x ", *(compressed + i));
    }
    printf("\n\n");

    if (lz77_uncompress(compressed, &original2) == -1)
        return -1;
    printf("original was:\n");
    for (i = 0; i < size; i++) {
        printf("%c", *(original2 + i));
    }

    return 0;
}

