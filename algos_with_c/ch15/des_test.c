#include <stdio.h>

#include "encrypt.h"


int main() {
    char plaintext[8] = "hello wo";
    char ciphertext[8], deciphered[8];
    char key[8] = "abcdefgh";

    printf("plaintext = %s\n", plaintext);

    des_encipher(plaintext, ciphertext, key);
    printf("ciphertext = %s\n", ciphertext);

    des_decipher(ciphertext, deciphered, key);
    printf("deciphered = %s\n", deciphered);

    return 0;
}

