#include <stdio.h>

#include "nummeths.h"


int main() {
    int n = 4;
    double x[4] = {-3.0, -2.0, 2.0, 3.0};
    double fx[4] = {-5.0, -1.1, 1.9, 4.8};
    int m = 4;
    double z[4] = {-2.5, 0.0, 1.0, 2.5};
    double pz[4];
    int i;

    if (interpol(x, fx, n, z, pz, m) != 0)
        return -1;

    for (i = 0; i < m; i++)
        printf("%f\n", pz[i]);

    return 0;
}

