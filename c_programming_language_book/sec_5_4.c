// Size of available space
#define ALLOCSIZE 10000

// Storage for alloc
static char allocbuf[ALLOCSIZE];
// Next free position
static char *allocp = allocbuf;

// Return pointer to n characters
char *alloc(int n)
{
    // If it fits
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        // Old p
        return allocp - n;
    } else // Not enough room
        return 0;
}


// Free storage pointed to by p
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

