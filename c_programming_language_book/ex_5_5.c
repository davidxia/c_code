#include <stdio.h>
#include <ctype.h>


void strncpy(char *s, char *t, int n);
void strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);


main()
{
    int n = 0;
    char s[100];
    char t[] = "this is a string";

    printf("t = %s\n", t);
    printf("How many chars to copy?\n");
    scanf("%d", &n);
    strncpy(s, t, n);
    printf("s = %s\n", s);

    printf("How many chars of t to concatenate to s?\n");
    scanf("%d", &n);
    strncat(s, t, n);
    printf("s = %s\n", s);

    printf("How many chars of s and t to compare?\n");
    scanf("%d", &n);
    printf("strncmp returned %d\n", strncmp(s, t, n));
}


/* strncpy: copy first n chars from t into s */
void strncpy(char *s, char *t, int n)
{
    if (n == 0) {
        *s = '\0';
        return;
    }

    int i = 0;
    while ((*s++ = *t++) && ++i < n)
        ;
    *s = '\0';
}


/* strncat: concatenate first n chars of t to s */
void strncat(char *s, char *t, int n)
{
    if (n < 1)
        return;

    // Go to end of string
    while (*++s)
        ;

    int i;
    for (i = 0; i < n; i++) {
        *s++ = *t++;
    }
}


/* strncmp: compare first n chars of s and t */
int strncmp(char *s, char *t, int n)
{
    int i;
    for (i = 0; *s == *t && i < n; i++) {
        s++; t++;
    }

    if (i == n)
        return 0;
    return *s - *t;
}

