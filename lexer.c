#include "lexer.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lexer {
    char *filename;
    FILE *file;
    bool eof;
    unsigned long index, line, column;
    int current;
    struct TokenVector *token_vector;
};

static void next_char(struct Lexer *lexer);
static const struct Token *get_token_eof(struct Lexer *lexer);
static const struct Token *get_token_number(struct Lexer *lexer);

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

    lexer->eof = false;
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

    while (lexer->current == ' ' || lexer->current == '\n') next_char(lexer);

    if (lexer->current == EOF) return get_token_eof(lexer);
    if (lexer->current >= '0' && lexer->current <= '9') return get_token_number(lexer);

    return NULL;
}

void next_char(struct Lexer *const lexer)
{
    if (lexer->current == '\n') {
        ++lexer->line;
        lexer->column = 0;
    }
    else {
        ++lexer->column;
    }

    ++lexer->index;
    lexer->current = fgetc(lexer->file);
}

const struct Token *get_token_eof(struct Lexer *const lexer)
{
    if (lexer->eof) return NULL;

    lexer->eof = true;

    return token_vector_append(
        lexer->token_vector,
        TOKEN_EOF,
        lexer->index,
        lexer->line,
        lexer->column,
        NULL
    );
}

const struct Token *get_token_number(struct Lexer *const lexer)
{
    const unsigned long index = lexer->index;
    const unsigned long line = lexer->line;
    const unsigned long column = lexer->column;

    char value[4096];
    size_t idx = 0;

    while (lexer->current >= '0' && lexer->current <= '9') {
        if (idx >= 4096) return NULL;
        value[idx++] = lexer->current;
        next_char(lexer);
    }

    return token_vector_append(
        lexer->token_vector,
        TOKEN_NUMBER,
        index,
        line,
        column,
        value
    );
}
