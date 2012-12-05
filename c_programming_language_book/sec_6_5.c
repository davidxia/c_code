#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAXWORD 100


// Tree node
struct tnode {
    // Points to the text
    char *word;
    // Number of occurrences
    int count;
    // Left child
    struct tnode *left;
    // Right child
    struct tnode *right;
};


// addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *, char *);
// treeprint: in-order print of tree
void treeprint(struct tnode *);
int getword(char *, int);


// Word frequency count
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);

    return 0;
}


// Get a (possibly pushed-back) character
int getch( void );
// Push character back on input
void ungetch( int );

#define BUFSIZE 100
// Buffer for ungetch
char buf[ BUFSIZE ];
// Next free position in buf
int bufp = 0;


int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}


int getch( void )
{
    return (bufp > 0) ? buf[ --bufp ] : getchar();
}


void ungetch( int c )
{
    if (bufp > BUFSIZE)
        printf( "ungetch: too many characters\n" );
    else
        buf[ bufp++ ] = c;
}



// talloc: make a tnod
struct tnode *talloc(void);
// Make a duplicate of s
char *strDup(char *);


struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    // A new word has arrived
    if (p == NULL) {
        // Make a new node
        p = talloc();
        p->word = strDup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        // Repeated word
        p->count++;
    else if (cond < 0)
        // Less than into left subtree
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}


void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}


struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}


char *strDup(char *s)
{
    char *p;

    // +1 for '\0'
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}

