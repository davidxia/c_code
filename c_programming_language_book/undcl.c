#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };


void dcl(void);
void dirdcl(void);


int gettoken(void);
int getch(void);
void ungetch(int);

// Type of last token
int tokentype;
// Last token string
char token[MAXTOKEN];
// Identifier name
char name[MAXTOKEN];
// Data type = char, int, etc.
char datatype[MAXTOKEN];
// Output string
char out[1000];


// undcl: convert word description to declaration
int main()
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
    }

    return 0;
}


// dcl: parse a declarator
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; ) {
        ns++;
    }
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}


// dirdcl: parse a direct declarator
void dirdcl(void)
{
    int type;

    if (tokentype =='(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) // Variable name
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}


// Return next token
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}


# define BUFSIZE 100


// Buffer for ungetch
char buf[BUFSIZE];
// Next free position in buf
int bufp = 0;


// Get a (possibly pushed back) char
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


// Push char back on input
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many chars\n");
    else
        buf[bufp++] = c;
}

