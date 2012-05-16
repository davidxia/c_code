#include <stdio.h>
#define BUFSIZE 100


/* Buffer for ungetch */
char buf[ BUFSIZE ];
/* Next free position in buf */
int bufp = 0;


/* Get a (possibly pushed-back) character */
int getch( void )
{
    return (bufp > 0) ? buf[ --bufp ] : getchar();
}


/* Push character back on input */
void ungetch( int c )
{
    if (bufp > BUFSIZE)
        printf( "ungetch: too many characters\n" );
    else
        buf[ bufp++ ] = c;
}

