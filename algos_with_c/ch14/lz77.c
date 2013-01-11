#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"
#include "compress.h"


static int compare_win(const unsigned char *window, const unsigned char *buffer,
                       int *offset, unsigned char *next) {
    int match, longest, i, j, k;

    /* Initialize the offset, altho it's valid only once a match is found */
    *offset = 0;

    /* If no match is found, prepare to return 0 and next symbol in look-ahead buffer */
    longest = 0;
    *next = buffer[0];

    /* Look for best match in look-ahead buffer and sliding window */
    for (k = 0; k < LZ77_WINDOW_SIZE; k++) {
        i = k;
        j = 0;
        match = 0;

        /* Determine how many symbols match in the sliding window at offset k */
        while (i < LZ77_WINDOW_SIZE && j < LZ77_BUFFER_SIZE - 1) {
            if (window[i] != buffer[j])
                break;

            match++;
            i++;
            j++;
        }

        /* Keep track of offset, length, and next symbol for best match */
        if (match > longest) {
            *offset = k;
            longest = match;
            *next = buffer[j];
        }
    }

    return longest;
}


int lz77_compress(const unsigned char *original, unsigned char **compressed, int size) {
    unsigned char window[LZ77_WINDOW_SIZE], buffer[LZ77_BUFFER_SIZE], *comp, *temp, next;
    int offset, length, remaining, hsize, ipos, opos, tpos, i, tbits, token;

    /* Make pointer to compressed data not valid until later */
    *compressed = NULL;

    /* Write header info */
    hsize = sizeof(int);
    if ((comp = (unsigned char *) malloc(hsize)) == NULL)
        return -1;
    memcpy(comp, &size, sizeof(int));

    /* Initialize the sliding window and look-ahead buffer */
    memset(window, 0, LZ77_WINDOW_SIZE);
    memset(buffer, 0, LZ77_BUFFER_SIZE);

    /* Load look-ahead buffer */
    ipos = 0;
    for (i = 0; i < LZ77_BUFFER_SIZE && ipos < size; i++) {
        buffer[i] = original[ipos];
        ipos++;
    }

    /* Compress data */
    opos = hsize * 8;
    remaining = size;

    while (remaining > 0) {
        if ((length = compare_win(window, buffer, &offset, &next)) != 0) {
            /* Encode a phrase token */
            token = 0x00000001 << (LZ77_PHRASE_BITS -1);

            /* Set offset where match was found in the sliding window */
            token = token | (offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS));

            /* Set length of match */
            token = token | (length << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS - LZ77_BUFLEN_BITS));

            /* Set next symbol in the look-ahead buffer after the match */
            token = token | next;

            /* Set number of bits in the token */
            tbits = LZ77_PHRASE_BITS;
        } else {
            /* Encode a symbol token */
            token = 0x00000000;

            /* Set the unmatched symbol */
            token = token | next;

            /* Set number of bits in the token */
            tbits = LZ77_SYMBOL_BITS;
        }

        /* Ensure that the token is in big-endian format */
        token = htonl(token);

        /* Write the token to the buffer of compressed data */
        for (i = 0; i < tbits; i++) {
            if (opos % 8 == 0) {
                /* Allocate another byte for buffer of compressed data */
                if ((temp = (unsigned char *) realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }

                comp = temp;
            }

            tpos = (sizeof(unsigned long) * 8) - tbits + i;
            bit_set(comp, opos, bit_get((unsigned char *) &token, tpos));
            opos++;
        }

        /* Adjust the phrase length to account for unmatched symbol */
        length++;

        /* Copy data from look-ahead buffer to sliding window */
        memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
        memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);

        /* Read more data into look-ahead buffer */
        memmove(&buffer[0], &buffer[length], LZ77_BUFFER_SIZE - length);
        for (i = LZ77_BUFFER_SIZE - length; i < LZ77_BUFFER_SIZE && ipos < size; i++) {
            buffer[i] = original[ipos];
            ipos++;
        }

        /* Adjust total symbols remaining by phrase length */
        remaining = remaining - length;
    }

    /* Point to the buffer of compressed data */
    *compressed = comp;

    /* Return the number of bytes in compressed data */
    return ((opos - 1) / 8) + 1;
}
