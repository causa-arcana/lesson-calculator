#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(const int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "No input files\n");
        exit(EXIT_FAILURE);
    }

    const char *const filename = argv[1];

    struct Lexer *lexer = lexer_new_from_filename(filename);

    if (!lexer) {
        fprintf(stderr, "Input file doesn't exist\n");
    }
    else {
        LEXER_DESTROY(lexer);
    }

    exit(EXIT_SUCCESS);
}
