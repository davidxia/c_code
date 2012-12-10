#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define STDIN 0
#define STDOUT 1
#define STDERR 2


/* cat: concatenate files using system calls */
int main(int argc, char *argv[])
{
    char buf[BUFSIZ];
    int fd;
    void filecopy(int, int, char *);
    char *prog = argv[0];           /* program name for errors */

    if (argc == 1)                  /* no args; copy standard input */
        filecopy(STDIN, STDOUT, buf);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fd, STDOUT, buf);
                close(fd);
            }

    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing STDOUT\n", prog);
        exit(2);
    }

    exit(0);
}


/* filecopy: copy file ifd to file ofd */
void filecopy(int ifd, int ofd, char *buf)
{
    int n;

    while ((n = read(ifd, buf, BUFSIZ)) > 0)
        write(ofd, buf, n);
}

