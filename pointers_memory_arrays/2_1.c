#include <stdio.h>

int my_array[] = {1,23,17,4,-5,100};
int *ptr;

int main(void)
{
    int i;
    /* point our pointer to first element of array.
     * This is the same as ptr = &my_array[0].
     * The name of an array is the address of the 1st element in the array
     */
    ptr = my_array; 

    printf("\n\n");
    for (i = 0; i < 6; i++)
    {
        printf("my_array[%d] = %d  ", i, my_array[i]);
        printf("ptr + %d = %d\n", i, *(ptr + i));
    }

    return 0;
}

