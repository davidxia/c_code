#include <stdio.h>

#include "nummeths.h"


int main() {
    int n = 9;
    double x[] = {-4, -3, -2, -1.5, -0.5, 1, 2, 3.5, 4};
    double y[] = {-3, -1, -2, -0.5, 1, 0, 1.5, 1.0, 2.5};
    double b1;
    double b0;

    lsqe(x, y, n, &b1, &b0);

    printf("b1 = %f\nb0 = %f\n", b1, b0);
    return 0;
}

