#include <stdio.h>
#include <string.h>


static char str[] = "STRING Z";

/* Implement an algorithm to determine if a string has all unique characters.
 * Assume ASCII character set.
 */
int has_unique_chars( char* s )
{
    if (s == NULL)
        return 1;

    int char_set[ 256 ] = { 0 };
    size_t len = strlen( s );
    int i;

    for (i = 0; i < len; i++) {
        if (char_set[ s[ i ] ])
            return 0;

        char_set[ s[ i ] ] = 1;
    }

    return 1;
}


/* Save space by using bit vector */
int has_unique_chars2( char* s )
{
    if (s == NULL)
        return 1;

    size_t len = strlen( s );
    int checker = 0;
    int val;
    int i;

    for (i = 0; i < len; i++) {
        val = s[ i ] - 'A';

        if (( checker & (1 << val) ) > 0 )
            return 0;

        checker |= (1 << val);
    }
    return 1;
}


main()
{
    printf( "%d\n", has_unique_chars( str ) );
    printf( "%d", has_unique_chars2( str ) );

    printf( "\n\n" );
}

