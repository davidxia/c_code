#include <stdio.h>
#include <ctype.h>
#include "calc.h"


/* getop: get next character or numeric operand */
int getop( char s[] )
{
    int i, c;

    while ( (s[ 0 ] = c = getch()) == ' ' || c == '\t')
        ;

    s[ 1 ] = '\0';
    if (!isdigit( c ) && c != '.') {
        // Not a number
        return c;
    }

    i = 0;
    // Collect integer part
    if (isdigit( c ))
        while (isdigit( s[ ++i ] = c = getch() ))
            ;

    // Collect fraction part
    if (c == '.')
        while (isdigit( s[ ++i ] = c = getch() ))
            ;

    s[ i ] = '\0';
    if (c != EOF)
        ungetch( c );

    return NUMBER;
}
