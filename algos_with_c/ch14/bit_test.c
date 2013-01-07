#include <stdio.h>
#include <limits.h>

#include "bit.h"


int main() {
    int pos, size = CHAR_BIT;
    unsigned char bits1[] = "1";
    unsigned char bits2[] = "0";
    unsigned char bits3[] = "10";
    unsigned char bitsx[CHAR_BIT];

    printf("bits in char = %d\n\n", CHAR_BIT * sizeof(char));

    printf("bits1 = \"%s\" = ", bits1);
    for (pos = 0; pos < CHAR_BIT; pos++)
        printf("%d", bit_get(bits1, pos));

    bit_set(bits1, 6, 1);
    printf("\n\nAfter setting seventh bit to 1:\nbits1 = \"%s\" = ", bits1);
    for (pos = 0; pos < CHAR_BIT; pos++)
        printf("%d", bit_get(bits1, pos));

    bit_xor(bits1, bits2, bitsx, CHAR_BIT);
    printf("\n\n\"%s\" XOR \"%s\" = ", bits1, bits2);
    for (pos = 0; pos < CHAR_BIT; pos++)
        printf("%d", bit_get(bitsx, pos));

    printf("\n\nbits3 = \"%s\" = ", bits3);
    for (pos = 0; pos < CHAR_BIT * 2; pos++) {
        if ((pos % 4) == 0)
            printf(" ");
        printf("%d", bit_get(bits3, pos));
    }

    bit_rot_left(bits3, CHAR_BIT * 2, 3);
    printf("\nbit_rot_left(bits3, %d, %d) = ", CHAR_BIT * 2, 3);
    for (pos = 0; pos < CHAR_BIT * 2; pos++) {
        if ((pos % 4) == 0)
            printf(" ");
        printf("%d", bit_get(bits3, pos));
    }

    return 0;
}


