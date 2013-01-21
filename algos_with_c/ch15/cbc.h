void cbc_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
                  const unsigned char *key, int size);

void cbc_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
                  const unsigned char *key, int size);

