#include <stdio.h>

/* count blanks, tabs, and newlines */

main()
{
    int numBlanks;
    int numTabs;
    int numLines;
    int c;

    numBlanks = numTabs = numLines = 0;

    while ( (c = getchar() ) != EOF) {
        if (c == '\n') {
            ++numLines;
            ++numBlanks;
        }

        if (c == '\t') {
            ++numTabs;
            ++numBlanks;
        }

        if (c == ' ') {
            ++numBlanks;
        }
    }

    printf( "Blanks: %d, tabs: %d, newlines: %d", numBlanks, numTabs, numLines );
}

