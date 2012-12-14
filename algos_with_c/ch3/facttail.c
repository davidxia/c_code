#include <stdio.h>


int facttail(int n, int a) {
    if (n < 2)
        return a;
    else
        return facttail(n - 1, n * a);
}


int main() {
    printf("facttail(5) = %d\n", facttail(5, 1));
    return 0;
}

