#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>


int minscanf(char *, char *, ...);


int main()
{
    char *line = "25 Dec 1988";
    char *fmt = "%d %s %d";
    int day, year;
    char *month;

    minscanf(line, fmt, &day, month, &year);
    printf("day = %d\nmonth = %s\nyear = %d\n", day, month, year);
    return 0;
}


/* minscanf: minimal scanf with variable argument list */
int minscanf(char *line, char *fmt, ...)
{
    va_list ap;     /* points to each unnamed arg in turn */
    char *p, *sval;
    int *ip;
    double decpt = 1, *dp;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {
        if (*p == '%') {
            p++;

            switch (*p) {
                case 'd':
                    while (isspace(*line))    /* skip whitespace */
                        line++;
                    ip = va_arg(ap, int *);
                    for (*ip = 0; isdigit(*line); line++) {
                        *ip = *ip * 10 + *line - '0';
                    }
                    break;
                case 'f':
                    while (isspace(*line))    /* skip whitespace */
                        line++;
                    dp = va_arg(ap, double *);
                    *dp = 0;
                    while (isdigit(*line)) {
                        *dp = *dp * 10 + atoi(line++);
                    }
                    if (*line++ == '.') {
                        while (isdigit(*line)) {
                            *dp = *dp * 10 + atoi(line++);
                            decpt *= 10.0;
                        }
                    }
                    *dp = *dp / decpt;
                    break;
                case 's':
                    while (isspace(*line))    /* skip whitespace */
                        line++;
                    sval = va_arg(ap, char *);
                    *sval = '\0';
                    while(isalpha(*line)) {
                        *sval++ = *line++;
                    }
                    *sval = '\0';
                    break;
                default:
                    break;
            }
        }
    }

    va_end(ap);
}

