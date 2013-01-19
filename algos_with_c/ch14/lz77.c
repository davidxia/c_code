#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bit.h"
#include "compress.h"
#define DEBUG 0


static void dump(const char *desc, int val, int size) {
    if (DEBUG) {
        int i;

        printf("%s = %d = ", desc, val);
        for (i = 0; i < size; i++) {
            if (i % 4 == 0) printf(" ");
            printf("%d", bit_get((unsigned char *) &val, i));
        }
        printf("\n");
    }
    return;
}


static int compare_win(const unsigned char *window, const unsigned char *buffer,
                       int *offset, unsigned char *next) {
    int match, longest, i, j, k;

    /* Initialize the offset, altho it's valid only once a match is found */
    *offset = 0;

    /* If no match found, prepare to return 0 and next symbol in look-ahead buffer */
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
            if (DEBUG) printf("PHRASE TOKEN\n");
            /* Encode a phrase token */
            token = 0x00000001;
            dump("token before", token, sizeof(int) * 8);
            token = 0x00000001 << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS);
            dump("token", token, sizeof(int) * 8);

            /* Set offset where match was found in the sliding window */
            dump("offset", offset, sizeof(int) * 8);
            token = token | (offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS));
            int offset_shifted = offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS);
            if (DEBUG) printf("bitshift = %d\n", LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS);
            dump("offset after bitshift", offset_shifted, sizeof(int) * 8);

            dump("token", token, sizeof(int) * 8);

            /* Set length of match */
            token = token | (length << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS - LZ77_BUFLEN_BITS));
            dump("length", length, LZ77_WINOFF_BITS);
            dump("token", token, sizeof(int) * 8);

            /* Set next symbol in the look-ahead buffer after the match */
            token = token | next;
            dump("next", next, sizeof(char) * 8);

            /* Set number of bits in the token */
            tbits = LZ77_PHRASE_BITS;
            dump("token", token, sizeof(int) * 8);
        } else {
            if (DEBUG) printf("SYMBOL TOKEN\n");
            /* Encode a symbol token */
            token = 0x00000000;

            /* Set the unmatched symbol */
            token = token | next;
            dump("next", next, sizeof(char) * 8);

            /* Set number of bits in the token */
            tbits = LZ77_SYMBOL_BITS;
            dump("token", token, sizeof(int) * 8);
        }

        /* Ensure that the token is in big-endian format */
        token = htonl(token);
        dump("token big endian", token, sizeof(int) * 8);

        /* Write the token to the buffer of compressed data */
        if (DEBUG) printf("tbits = %d\n", tbits);
        for (i = 0; i < tbits; i++) {
            if (opos % 8 == 0) {
                /* Allocate another byte for buffer of compressed data */
                if ((temp = (unsigned char *) realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }

                comp = temp;
            }

            /* Book had sizeof(unsigned long) which I think is wrong */
            /* Calculating appropriate tpos for big endian format */
            tpos = (sizeof(int) * 8) - tbits + i;
            if (DEBUG) printf("tpos = %d, opos = %d\n", tpos, opos);

            bit_set(comp, opos, bit_get((unsigned char *) &token, tpos));

            if (DEBUG) {
                printf("comp = ");
                int j;
                for (j = 0; j <= opos; j++) {
                    if (j % 4 == 0) printf(" ");
                    printf("%d", bit_get(comp, j));
                }
                printf("\n");
            }
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


int lz77_uncompress(const unsigned char *compressed, unsigned char **original) {
    unsigned char window[LZ77_WINDOW_SIZE], buffer[LZ77_BUFFER_SIZE], *orig, *temp, next;
    int offset, length, remaining, hsize, size, ipos, opos, tpos, state, i;

    /* Make pointer to original data not valid until later */
    *original = orig = NULL;

    /* Get header information */
    hsize = sizeof(int);
    memcpy(&size, compressed, sizeof(int));

    /* Initialize sliding window and look-ahead buffer */
    memset(window, 0, LZ77_WINDOW_SIZE);
    memset(buffer, 0, LZ77_BUFFER_SIZE);

    /* Uncompress the data */
    ipos = hsize * 8;
    opos = 0;
    remaining = size;
    while (remaining > 0) {
        /* Get next bit in compressed data */
        state = bit_get(compressed, ipos);
        ipos++;

        if (state == 1) {
            /* Handle processing a phrase token */
            memset(&offset, 0, sizeof(int));
            for (i = 0; i < LZ77_WINOFF_BITS; i++) {
                tpos = (sizeof(int) * 8) - LZ77_WINOFF_BITS + i;
                bit_set((unsigned char *) &offset, tpos, bit_get(compressed, ipos));
                ipos++;
            }

            memset(&length, 0, sizeof(int));
            for (i = 0; i < LZ77_BUFLEN_BITS; i++) {
                tpos = (sizeof(int) * 8) - LZ77_BUFLEN_BITS + i;
                bit_set((unsigned char *) &length, tpos, bit_get(compressed, ipos));
                ipos++;
            }

            next = 0x00;
            for (i = 0; i < LZ77_NEXT_BITS; i++) {
                tpos = (sizeof(unsigned char) * 8) - LZ77_NEXT_BITS + i;
                bit_set((unsigned char *) &next, tpos, bit_get(compressed, ipos));
                ipos++;
            }

            /* Ensure offset and length have correct byte ordering for system */
            offset = ntohl(offset);
            length = ntohl(length);

            /* Write the phrase from window to buffer of original data */
            i = 0;
            if (opos > 0) {
                if ((temp = (unsigned char *) realloc(orig, opos + length + 1)) == NULL) {
                    free(orig);
                    return -1;
                }

                orig = temp;
            } else {
                if ((orig = (unsigned char *) malloc(length + 1)) == NULL)
                    return -1;
            }

            while (i < length && remaining > 0) {
                orig[opos] = window[offset + i];
                opos++;

                /* Record each symbol in look-ahead buffer until ready to update
                 * sliding window
                 */
                buffer[i] = window[offset + i];
                i++;

                /* Adjust the total symbols remaining to account for each symbol consumed */
                remaining--;
            }

            /* Write the unmatched symbol to the buffer of original data */
            if (remaining > 0) {
                orig[opos] = next;
                opos++;

                /* Also record this symbol in look-ahead buffer */
                buffer[i] = next;

                /* Adjust the total symbols remaining to account for each symbol consumed */
                remaining--;
            }

            /* Adjust phrase length to account for unmatched symbol */
            length++;
        } else { /* Handle processing a symbol token */
            next = 0x00;
            for (i = 0; i < LZ77_NEXT_BITS; i++) {
                tpos = (sizeof(unsigned char) * 8) - LZ77_NEXT_BITS + i;
                bit_set((unsigned char *) &next, tpos, bit_get(compressed, ipos));
                ipos++;
            }

            /* Write the symbol to the buffer of original data */
            if (opos > 0) {
                if ((temp = (unsigned char *) realloc(orig, opos + 1)) == NULL) {
                    free(orig);
                    return -1;
                }

                orig = temp;
            } else {
                if ((orig = (unsigned char *) malloc(1)) == NULL)
                    return -1;
            }

            orig[opos] = next;
            opos++;

            /* Record the symbol in the look-ahead buffer until ready to update sliding window */
            if (remaining > 0)
                buffer[0] = next;

            /* Adjust total symbols remaining to account for unmatched symbol */
            remaining--;

            /* Set phrase length to account for unmatched symbol */
            length = 1;
        }

        /* Copy look-ahead buffer into sliding window */
        memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
        memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);
    }

    /* Point to buffer of original data */
    *original = orig;

    /* Return number of bytes in original data */
    return opos;
}

