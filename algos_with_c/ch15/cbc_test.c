#include <stdio.h>

#include "encrypt.h"
#include "cbc.h"


void hex_dump(void *data, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%x ", *((unsigned char *) data + i));
    }
    return;
}


int main() {
    int size = 16, i;
    char plaintext[] = "hello world, thi";
    char ciphertext[size], deciphered[size];
    char key[8] = "abcdefgh";

    printf("plaintext = '%s', hex:\n", plaintext);
    hex_dump(plaintext, size);
    printf("\n\n");

    cbc_encipher(plaintext, ciphertext, key, size);
    printf("ciphertext = '%s', hex:\n", ciphertext);
    hex_dump(ciphertext, size);
    printf("\n\n");

    cbc_decipher(ciphertext, deciphered, key, size);
    printf("deciphered = '%s', hex:\n", deciphered);
    hex_dump(deciphered, size);
    printf("\n\n");

    return 0;
}


