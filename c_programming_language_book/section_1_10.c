#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int max;                /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */

int mygetline(void);
void copy(void);

/* print the longest input */
main()
{
    int len;                /* current line length */

    max = 0;
    while ((len = mygetline()) > 0)
        if (len > max) {
            max = len;
            copy();
        }
    if (max > 0) /* there was a line */
        printf("%s", longest);
    return 0;
}

/* mygetline: read a line into s, return length */
int mygetline(void)
{
    int c, i;

    for (i = 0; i < MAXLINE - 1 && (c=getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(void)
{
    int i;

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}

