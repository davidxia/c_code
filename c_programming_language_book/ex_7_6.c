#include <stdio.h>
#include <stdlib.h>


#define MAXCHARS 2048

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int c1, c2, isdiff = 0;
    char line1[MAXCHARS], line2[MAXCHARS], *line1p, *line2p;

    if (argc != 3) {
        fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(1);
    }

    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "can't open %s\n", argv[2]);
        exit(1);
    }

    while (isdiff == 0 && fgets(line1, MAXCHARS, fp1) != NULL && fgets(line2, MAXCHARS, fp2) != NULL) {
        line1p = line1;
        line2p = line2;

        /* could also use strcmp here */
        for (c1 = *line1p, c2 = *line2p; *line1p && *line2p; line1p++, line2p++) {
            c1 = *line1p;
            c2 = *line2p;

            if (c1 != c2)
                isdiff = 1;
        }
    }

    if (isdiff)
        printf("%s: %s%s: %s", argv[1], line1, argv[2], line2);

    exit(0);
}

