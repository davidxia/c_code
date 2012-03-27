#include <stdio.h>

/* print Celsius-Fahrenheit table
   for celsius = -20, -10, ..., 150 */

main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = -20;      /* lower limit of temperature scale */
    upper = 150;    /* upper limit */
    step = 10;      /* step size */
  
    celsius = lower;
    printf("  C    F\n-----------\n");
    while (celsius <= upper) {
        fahr = (9.0/5.0) * celsius + 32.0;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

