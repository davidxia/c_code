#include <stdio.h>


int itoa(int n, char s[]);

main()
{
    char s[3];
    s[0] = '\0';

    itoa(125, s);
    printf("%s\n", s);
}

/* itoa: convert int to chars using recursion */
int itoa(int n, char s[])
{
    int i = 0;

    if (n / 10) {
        // Return the index of the end of the string
        i = itoa(n / 10, s);
    }
    s[i] = n % 10 + '0';
    // Mark the end of the string
    s[++i] = '\0';
    return i;
}

