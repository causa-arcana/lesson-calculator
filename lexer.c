#include "lexer.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lexer {
    char *filename;
    FILE *file;
    unsigned long index, line, column;
    unsigned char current;
    struct TokenVector *token_vector;
};

struct Lexer *lexer_new_from_filename(const char *const filename)
{
    assert(filename != NULL);

    struct Lexer *lexer = malloc(sizeof(struct Lexer));
    if (lexer == NULL) goto fail0;
    memset(lexer, 0, sizeof(struct Lexer));

    lexer->filename = malloc(strlen(filename) + 1);
    if (lexer->filename == NULL) goto fail1;
    strcpy(lexer->filename, filename);

    lexer->file = fopen(lexer->filename, "r");
    if (lexer->file == NULL) goto fail2;

    lexer->index = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current = fgetc(lexer->file);

    lexer->token_vector = token_vector_new();
    if (lexer->token_vector == NULL) goto fail2;

    return lexer;

fail2:
    free(lexer->filename);
fail1:
    free(lexer);
fail0:
    return NULL;
}

void lexer_destroy(struct Lexer *const lexer)
{
    assert(lexer != NULL);
    assert(lexer->filename != NULL);
    assert(lexer->file != NULL);
    assert(lexer->token_vector != NULL);

    token_vector_destroy(lexer->token_vector);
    fclose(lexer->file);
    free(lexer->filename);
    free(lexer);
}

const struct Token *lexer_get_token(struct Lexer *const lexer)
{
    assert(lexer != NULL);

    return NULL;
}
