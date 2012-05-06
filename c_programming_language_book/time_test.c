/*
 * A timer in C
 * author: Danny Battison
 * contact: gabehabe@hotmail.com
 */

#include <time.h>
#include <stdio.h>

clock_t BeginTimer()
{
    //timer declaration
    clock_t Begin; //initialize Begin

    Begin = clock() * CLOCKS_PER_SEC; //start the timer

    return Begin;
}
clock_t EndTimer(clock_t begin)
{
    clock_t End;
    End = clock() * CLOCKS_PER_SEC;   //stop the timer
    return End;
}

int main ()
{
    double begin = BeginTimer();
    printf ("Timer set to: %.2f\n", begin); // print the initialised timer (0)

    // process to be timed goes here
    printf ("Enter something to stop the timer: ");
    char input;
    scanf ("%c", &input);

    // variable declarations used for time calculation
    float elapTicks;
    float elapMilli, elapSeconds, elapMinutes;

    // variable definitions on to calculate time taken
    elapTicks = EndTimer(begin);    // stop the timer, and calculete the time taken
    elapMilli = elapTicks/1000;     // milliseconds from Begin to End
    elapSeconds = elapMilli/1000;   // seconds from Begin to End
    elapMinutes = elapSeconds/60;   // minutes from Begin to End

    printf ("Milliseconds passed: %.2f\n", elapMilli);
    printf ("Seconds passed: %.2f\n", elapSeconds);
    printf ("Minutes passed: %.2f", elapMinutes);

    // hold the window open
    char dummy;
    scanf ("%c", &dummy);
    return 0;
}
