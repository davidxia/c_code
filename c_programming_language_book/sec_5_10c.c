#include <stdio.h>
#include <string.h>


// Maximum input line length
#define MAXLINE 1000

int getLine(char s[], int lim);


// Find all lines matching pattern from 1st arg
main(int argc, char *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if (argc !=2)
        printf("Usage: find pattern\n");
    else
        while (getLine(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}


// getLine: get line into s, return length
int getLine(char s[], int lim)
{
    int c, i;
    i = 0;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

