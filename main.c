#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"

int main(const int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "No input files\n");
        exit(EXIT_FAILURE);
    }

    const char *const filename = argv[1];

    struct Lexer *lexer = lexer_new_from_filename(filename);

    if (lexer == NULL) {
        fprintf(stderr, "Input file doesn't exist\n");
        exit(EXIT_FAILURE);
    }

    const struct Token *token = lexer_get_token(lexer);

    while (token != NULL) {
        token_println(token);
        token = lexer_get_token(lexer);
    }

    LEXER_DESTROY(lexer);

    exit(EXIT_SUCCESS);
}
