#include <stdarg.h>
#include <stdio.h>


void minprintf(char *fmt, ...);


int main()
{
    minprintf("Hi %s %d times\n", "David", 40);
}


// minprintf: minimal printf with variable argument list
void minprintf(char *fmt, ...)
{
    // Points to each unnamed arg in turn
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    // Make ap point to 1st unnamed arg
    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }

    // Clean up when done
    va_end(ap);
}

