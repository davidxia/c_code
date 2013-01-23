#include <stdio.h>

#include "encrypt.h"


int main() {
    Huge plaintext = 24800;
    Huge ciphertext, deciphered;
    /* p = 1039, q = 373, n = pq = 387547 */
    Huge e = 17, n = 387547, d = 204425;
    RsaPubKey pubkey = { .e = e, .n = n };
    RsaPriKey prikey = { .d = d, .n = n };

    printf("plaintext = '%lu', hex:\n", plaintext);

    rsa_encipher(plaintext, &ciphertext, pubkey);
    printf("ciphertext = '%lu', hex:\n", ciphertext);

    rsa_decipher(ciphertext, &deciphered, prikey);
    printf("deciphered = '%lu', hex:\n", deciphered);

    return 0;
}

