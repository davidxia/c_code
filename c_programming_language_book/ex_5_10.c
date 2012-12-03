#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Max size of operand or operator
#define MAXOP 100
// Signal that a number was found
#define NUMBER '0'
// Maximum depth of val stack
#define MAXVAL 100
#define BUFSIZE 100


int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);


// Next free stack position
int sp;
// Value stack
double val[MAXVAL];
// Buffer for ungetch
char buf[BUFSIZE];
// Next free position in buf
int bufp = 0;


// Reverse Polish calculator
// For multiplication, must escape with \* or else it globs
main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while (--argc > 0) {
        type = getop(*++argv);
        switch (type) {
            case NUMBER:
                push(atof(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("Error: zero divisor\n");
                break;
            default:
                printf("Error: unknown command %s\n", *argv);
                break;
        }
    }

    printf("\t%.8g\n", pop());
    return 0;
}


// push: push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: stack full, can't push %g\n", f);
}


// pop: pop and return top value from stack
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: stack empty\n");
        return 0.0;
    }
}


// getop: get next character or numeric operand
int getop(char *s)
{
    int i, c;

    if (!isdigit(*s) && *s != '.') {
        // Not a number
        return *s;
    }

    // Collect integer part
    if (isdigit(*s))
        while (isdigit(*++s))
            ;

    // Collect fraction part
    if (*s == '.')
        while (isdigit(*++s))
            ;

    return NUMBER;
}


// Get a (possibly pushed-back) character
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


// Push character back on input
void ungetch(int c)
{
    if (bufp > BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

