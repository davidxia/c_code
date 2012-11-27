#include <stdio.h>

/* Maximum input line length */
#define MAXLINE 1000

int strLen( char str[] );
int getLine( char line[], int max );
int strrindex( char source[], char searchfor[] );

/* Pattern to search for */
char pattern[] = "ould";

/* Find all lines matching pattern */
main()
{
    char line[ MAXLINE ];
    int rindex;

    while (getLine( line, MAXLINE ) > 0) {
        rindex = strrindex( line, pattern );
        if ( rindex >= 0 ) {
            printf( "Rightmost position of %s in %s: %d", pattern, line, rindex );
        }
    }
}


int strLen( char s[] )
{
    int i;

    i = 0;
    while (s[ i ] != '\0')
        ++i;
    return i;
}


/* getline: get line into s, return length */
int getLine( char s[], int lim )
{
    int c, i;
    i = 0;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[ i++ ] = c;
    if (c == '\n')
        s[ i++ ] = c;
    s[ i ] = '\0';

    return i;
}


/* strrindex: return index of t in s, -1 if none */
int strrindex( char s[], char t[] )
{
    int i, j, k;

    for (i = strLen( s ) - 2; i >= 0; i--) {
        for (j = i, k = strLen( t ) - 1; k >= 0 && s[ j ] == t[ k ]; j--, k--)
            ;
        if (k < 0)
            return j + 1;
    }

    return -1;
}

