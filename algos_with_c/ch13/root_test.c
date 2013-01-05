#include <stdio.h>
#include <math.h>

#include "nummeths.h"


double f(double x) {
    return pow(x, 3) - pow(x, 2) - 3 * x + 1.8;
}

double g(double x) {
    return 3 * pow(x, 2) - 2 * x - 3;
}


int main() {
    int n = 5, i;
    double delta = 0.0001;
    double x[5];
    x[0] = -2.0;

    if (root(f, g, x, &n, delta) != 0)
        return -1;

    for (i = 0; i < n; i++)
        printf("%f\n", x[i]);

    return 0;
}

