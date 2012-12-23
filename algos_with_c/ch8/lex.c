#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "chtbl.h"
#include "lex.h"
#include "symbol.h"


Token lex(const char *istream, CHTbl *symtbl) {
    Token token;
    Symbol *symbol;
    int length, retval, i;

    /* Allocate space for a symbol */
    if ((symbol = (Symbol *) malloc(sizeof(Symbol))) == NULL)
        return error;

    /* Process next token */
    if ((symbol->lexeme = next_token(istream)) == NULL) {
        /* Return that there is no more input */
        free(symbol);
        return lexit;
    } else {
        /* Determine token type */
        symbol->token = digit;
        length = strlen(symbol->lexeme);

        for (i = 0; i < length; i++) {
            if (!isdigit(symbol->lexeme[i]))
                symbol->token = other;
        }

        memcpy(&token, &symbol->token, sizeof(Token));

        /* Insert symbol into symbol table */
        if ((retval = chtbl_insert(symtbl, symbol)) < 0) {
            free(symbol);
            return error;
        } else if (retval == 1) {
            /* Symbol already in table */
            free(symbol);
        }
    }

    /* Return token for parser */
    return token;
}

