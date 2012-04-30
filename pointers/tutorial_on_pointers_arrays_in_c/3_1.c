#include <stdio.h>

char strA[80] = "A string to be used for demonstration purposes";
char strB[80] = "12345678901234567890123456789012345678901234567890";

int main(void)
{
    char *pA;           /* a pointer to type character */
    char *pB;           /* another pointer to type character */

    puts(strA);         /* show string A */

    pA = strA;          /* point pA at string A */
    puts(pA);           /* show what pA is pointing to */

    pB = strB;          /* point pB at string B */
    puts(pB);
    putchar('\n');

    while (*pA != '\0')
    {
        *pB++ = *pA++;
    }
    *pB = '\0';
    puts(strB);         /* show string B */

    return 0;
}

