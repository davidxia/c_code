#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int get(int, long, char *, int);


int main(int argc, char *argv[])
{
    int pos, fd;
    char buf[BUFSIZ];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file offset\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY, 0)) == -1) {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
        exit(1);
    }

    pos = atoi(argv[2]);
    if (get(fd, pos, buf, 64) != -1)
        printf("%s\n", buf);

    return 0;
}


/* get; read n bytes from position pos */
int get(int fd, long pos, char *buf, int n)
{
    if (lseek(fd, pos, 0) >= 0)    /* get to pos */
        return read(fd, buf, n);
    else
        return -1;
}

