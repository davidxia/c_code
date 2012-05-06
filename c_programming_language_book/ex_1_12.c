#include <stdio.h>

#define IN  1 /* inside a word */
#define OUT 0 /* outside a word */


/* prints input one word per line */
main()
{
    int c, state;

    state = OUT;
    while ( (c = getchar() ) != EOF) {
        if ( state == IN && (c == ' ' || c == '\t' || c == '\n' ) ) {
            printf( "\n" );
            state = OUT;
        } else if (c != ' ' && c != '\t' && c != '\n' ) {
            printf( "%c", c );
            state = IN;
        }
    }
}

