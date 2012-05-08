#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>     // strcat

char* print_bits( int v ) {
    int i;
    for (i = (sizeof( v ) * CHAR_BIT ) - 1; i >= 0; i--)
        putchar( '0' + ( (v >> i) & 1) );
}

/* Function to get number of set bits in binary representation of passed binary number. */
int count_bits( int n ) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Sparse Ones runs in time proportional to the number of 1 bits.
 * The mystical line n &= (n – 1) simply sets the rightmost 1 bit in n to 0.
 */
int sparse_ones( int n ) {
    int count = 0;
    while (n) {
        n &= (n-1);
        count++;
    }
    return count;
}

/* Dense Ones runs in time proportional to the number of 0 bits.
 * It is the same as Sparse Ones, except that it first toggles
 * all bits (n ~= -1), and continually subtracts the number of
 * 1 bits from sizeof(int).
 */
int dense_ones( unsigned int n ) {
    int count = CHAR_BIT * sizeof( int );
    n = ~n;
    while (n) {
        count--;
        n &= (n-1);
    }
    return count;
}


int main() {

    int n;
    printf( "Enter an integer:\n" );
    scanf( "%d", &n );
    print_bits( n );
    printf( "\n\n" );

    printf( "Simple method of checking each bit: %d\n", count_bits( n ) );
    printf( "Now with sparse ones method: %d\n", sparse_ones( n ) );
    printf( "Now with dense ones method: %d\n", dense_ones( n ) );
    return 0;
}

