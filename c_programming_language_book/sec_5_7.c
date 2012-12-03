#include <stdio.h>


int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);


main()
{
    int year, month, day, yearday;

    printf("Enter year, month, and day (e.g. '2012/11/30')\n");
    scanf("%d/%d/%d", &year, &month, &day);
    yearday = day_of_year(year, month, day);
    printf("day_of_year returned %d\n", yearday);

    month_day(year, yearday, &month, &day);
    printf("month_day returned month = %d, day = %d\n", month, day);
}


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}


// month_day: set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

