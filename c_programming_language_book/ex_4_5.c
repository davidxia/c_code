#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


/* Max size of operand or operator */
#define MAXOP 100
/* Signal that a number was found */
#define NUMBER '0'
#define SIN '1'
#define EXP '2'
#define POW '3'
/* Maximum depth of val stack */
#define MAXVAL 100
#define BUFSIZE 100


int getop( char [] );
void push( double );
double pop( void );
int getch( void );
void ungetch( int );


/* Next free stack position */
int sp;
/* Value stack */
double val[ MAXVAL ];
/* Buffer for ungetch */
char buf[ BUFSIZE ];
/* Next free position in buf */
int bufp = 0;


/* Reverse Polish calculator */
main()
{
    int type;
    double op2;
    char s[ MAXOP ];

    while ((type = getop( s )) != EOF) {
        switch (type) {
            case NUMBER:
                push( atof( s ) );
                break;
            case '+':
                push( pop() + pop() );
                break;
            case '*':
                push( pop() * pop() );
                break;
            case '-':
                op2 = pop();
                push( pop() - op2 );
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push( pop() / op2 );
                else
                    printf( "Error: zero divisor\n" );
                break;
            case SIN:
                push( sin( pop() ) );
                break;
            case EXP:
                push( exp( pop() ) );
                break;
            case POW:
                op2 = pop();
                push( pow( pop(), op2 ) );
                break;
            case '\n':
                printf( "\t%.8g\n", pop() );
                break;
            default:
                printf( "Error: unknown command %s\n", s );
                break;
        }
    }

    return 0;
}


/* getop: get next character or numeric operand */
int getop( char s[] )
{
    int i, c;

    while ( (s[ 0 ] = c = getch()) == ' ' || c == '\t')
        ;

    s[ 1 ] = '\0';
    if (!isdigit( c ) && c != '.' && !isalpha( c )) {
        // Not a number
        return c;
    }

    if (isalpha( c )) {
        while (isalpha( s[ ++i ] = c = getch() ))
            ;
        ungetch( c );
        s[ i ] = '\0';

        if ( strcmp(s, "sin") == 0 ) {
            return SIN;
        } else if ( strcmp(s, "exp") == 0 ) {
            return EXP;
        } else if ( strcmp(s, "pow") == 0 ) {
            return POW;
        } else {
            return 0;
        }
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


/* push: push f onto value stack */
void push( double f )
{
    if (sp < MAXVAL)
        val[ sp++ ] = f;
    else
        printf( "Error: stack full, can't push %g\n", f );
}


/* pop: pop and return top value from stack */
double pop( void )
{
    if (sp > 0)
        return val[ --sp ];
    else {
        printf( "Error: stack empty\n" );
        return 0.0;
    }
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

