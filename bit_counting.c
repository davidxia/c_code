#include <stdlib.h>
#include <stdio.h>
#include <string.h>     // strcat

char* print_bits(int v) {
    for(int i = (sizeof(v)*8)-1; i >= 0; i--)
        putchar('0' + ((v >> i) & 1));
}

/*
 Function to get number of set bits in binary
 representation of passed binary number.
*/
int count_bits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/*
 Sparse Ones runs in time proportional to the number
 of 1 bits. The mystical line n &= (n – 1) simply sets
 the rightmost 1 bit in n to 0.
*/
int count_bits2(int n) {
    int count = 0;
    while (n) {
        n &= (n-1);
        count++;
    }
    return count;
}

/*
 Dense Ones runs in time proportional to the number of 0 bits.
 It is the same as Sparse Ones, except that it first toggles
 all bits (n ~= -1), and continually subtracts the number of
 1 bits from sizeof(int).
*/
int count_bits3(unsigned int n) {
    int count = 8 * sizeof(int);
    n = ~n;
    while (n) {
        count--;
        n &= (n-1);
    }
    return count;
}


int main() {
    printf("Let's count set bits in an integer!\n");
    int i = 15;
    printf("Integer: %d\n", i);
    printf("Simple method of checking each bit: %d\n", count_bits(i));
    printf("Now with sparse ones method: %d\n", count_bits2(i));
    printf("Now with dense ones method: %d\n", count_bits3(i));
    return 0;
}