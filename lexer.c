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

    fclose(lexer->file);
    free(lexer->filename);
    free(lexer);
}

const struct Token *lexer_get_token(struct Lexer *const lexer)
{
    assert(lexer != NULL);

    return NULL;
}
