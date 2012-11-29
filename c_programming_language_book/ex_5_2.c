#include <stdio.h>
#include <ctype.h>


#define BUFSIZE 100


int getfloat(float *pn);
int getch(void);
void ungetch(int);

/* Buffer for ungetch */
char buf[ BUFSIZE ];
/* Next free position in buf */
int bufp = 0;

main()
{
    float n;
    // Get first float if it exists
    if (getfloat(&n) != EOF)
        printf("%f\n", n);
    // Get second float if it exists
    if (getfloat(&n) != EOF)
        printf("%f\n", n);
}


/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    float decimal_place = 1;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    // Handle decimal point, if any
    if (c == '.') {
        c = getch();
    }

    // Collect fractional part of the float
    while (isdigit(c)) {
        *pn = 10 * *pn + (c - '0');
        decimal_place *= 10;
        c = getch();
    }

    *pn *= sign / decimal_place;
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

