#include <stdio.h>

/* print histogram of length of words in input */
main()
{
    int c, i, word_length;
    int word_lengths[30];

    word_length = 0;
    for (i = 0; i < 30; ++i)
        word_lengths[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\n' && c != '\t')
            ++word_length;
        else if (word_length > 0) {
            ++word_lengths[word_length - 1];
            word_length = 0;
        }
    }

    printf("word lengths = ");
    for (i = 0; i < 30; ++i)
        printf(" %d", word_lengths[i]);
}

