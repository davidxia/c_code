#include <stdio.h>


// Max input line size
#define MAXLINE 100
#define TAB2SPACE 4


// Current input line
char line[MAXLINE];
int getLine(void);


int main()
{
    int i, t;
    int spacecount, len;

    while ((len = getLine()) > 0) {
        spacecount = 0;
        for (i = 0; i < len; i++) {
            if (line[i] == ' ')
                spacecount++;
            if (line[i] != ' ')
                // Reset counter
                spacecount = 0;
            // Now we have enough spaces to replace with a tab
            if (spacecount == TAB2SPACE) {
                // Move back three chars replace space with tab
                i -= 3;
                len -= 3;
                line[i] = '\t';

                // Now move all chars to the right into the places we removed
                for (t = i +1; t < len; t++)
                    line[t] = line[t + 3];

                // Now set counter back to zero and move end of string back 3 spaces
                spacecount = 0;
                line[len] = '\0';
            }
        }
        printf("%s", line);
    }
    return 0;
}


int getLine(void)
{
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

