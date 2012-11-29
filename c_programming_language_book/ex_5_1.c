#include <stdio.h>
#include <ctype.h>


#define BUFSIZE 100


int getint(int *pn);
int getch(void);
void ungetch(int);

/* Buffer for ungetch */
char buf[ BUFSIZE ];
/* Next free position in buf */
int bufp = 0;

main()
{
    int n;
    // Get first integer if it exists
    if (getint(&n) != EOF)
        printf("%d\n", n);
    // Get second integer if it exists
    if (getint(&n) != EOF)
        printf("%d\n", n);
}


/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign, sawsign;

    // Skip white space
    while (isspace(c = getch()))
        ;

    // It is not a number
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    // Get the sign
    sign = (c == '-') ? -1 : 1;

    // Get the next char
    if (sawsign = (c == '+' || c == '-'))
        c = getch();

    // If next char is not a digit, put sign char back onto input as well
    if (!isdigit(c)) {
        ungetch(c);
        if (sawsign)
            ungetch((sign == -1) ? '-' : '+');
        return 0;
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

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

