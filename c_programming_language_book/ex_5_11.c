#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BUFFER   1024
#define SPACE        ' '
#define TAB          '\t'


int CalculateNumberOfSpaces(int offset, int tabsize)
{
    return tabsize - (offset % tabsize);
}


// K&R's getLine() function from p29
int getLine(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}


int main(void)
{
    char  buffer[MAX_BUFFER];
    // A good test value
    int tabsize = 5;

    int i, j, k, l;

    while (getLine(buffer, MAX_BUFFER) > 0) {
        for (i = 0, l = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == TAB) {
                j = CalculateNumberOfSpaces(l, tabsize);
                for (k = 0; k < j; k++) {
                    putchar(SPACE);
                    l++;
                }
            } else {
                putchar(buffer[i]);
                l++;
            }
        }
    }

    return 0;
}
