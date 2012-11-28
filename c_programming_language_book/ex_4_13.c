#include <stdio.h>
#include <string.h>


/* reverse: reverse string s in place using recursion */
void reverse( char s[], int left, int right )
{
    if (left >= right)
        return;

    int temp = s[ left ];
    s[ left ] = s[ right ];
    s[ right ] = temp;
    reverse( s, ++left, --right);
}


/* itoa: convert n to characters in s */
void itoa( int n, char s[] )
{
    int i, sign, left, right;

    // record sign
    if ( (sign = n) < 0 ) {
        // make n positive
        n = -n;
    }

    i = 0;

    // generate digits in reverse order
    do {
        // Get next digit
        s[ i++ ] = n % 10 + '0';
    // Delete it
    } while ( (n /= 10) > 0 );

    if (sign < 0)
        s[ i++ ] = '-';

    s[ i ] = '\0';

    left = 0;
    right = strlen( s ) - 1;
    reverse( s, left, right );
}

main()
{
    char s[ 100 ];
    itoa( 123, s );
    printf( "%s", s );
}

