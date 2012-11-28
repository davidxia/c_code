#include <stdio.h>


#define swap(t, x, y) do{t z = x; x = y; y = z;} while (0)


main()
{
    int x = 1, y = 2;
    printf("x: %d, y: %d\n", x, y);
    swap(int, x, y);
    printf("x: %d, y: %d\n", x, y);
}

