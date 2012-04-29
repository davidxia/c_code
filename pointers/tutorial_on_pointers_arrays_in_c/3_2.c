#include <stdio.h>

void *my_intcpy(int *ptrA, int *ptrB, int n)
{
    int *p = ptrA;
    int i;
    for (i = 0; i < n; i++)
    {
        *p++ = *ptrB++;
    }
    *p = '\0';
}

int main(void)
{
    int arrA[80] = {1, 2, 3, 4, 5};
    int arrB[80];
    int i;

    for (i = 0; i < 5; i++)
    {
        printf("%d", arrA[i]);
        printf("%d", arrB[i]);
    }

    my_intcpy(arrA, arrB, 5);

    putchar('\n');
    for (i = 0; i < 5; i++)
    {
        printf("%d", arrA[i]);
        printf("%d", arrB[i]);
    }
    
    return 0;
}

