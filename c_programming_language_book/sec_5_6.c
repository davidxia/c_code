#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Max #lines to be sorted
#define MAXLINES 5000

// Pointers to text lines
char *lineptr[MAXLINES];


int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qSort(char *lineptr[], int left, int right);


// Sort input lines
main()
{
    // Number of input lines read
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qSort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}


// Max length of any input line
#define MAXLEN 1000
int getLine(char *, int);
char *alloc(int);


// Readlines: read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            // Delete newline
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}


// writelines: write output lines
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}


// getLine: read a line into s, return length
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


// qSort: sort v[left]...v[right] into increasing order
void qSort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    // Do nothing if array contains fewer than 2 elements
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qSort(v, left, last - 1);
    qSort(v, last + 1, right);
}


// swap: interchange v[i] and v[j]
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

