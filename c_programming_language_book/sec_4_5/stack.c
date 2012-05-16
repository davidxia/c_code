#include <stdio.h>
#include "calc.h"


/* Maximum depth of val stack */
#define MAXVAL 100
#define BUFSIZE 100


/* Next free stack position */
int sp;
/* Value stack */
double val[ MAXVAL ];


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

