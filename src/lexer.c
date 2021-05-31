#include "lexer.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDENT_START(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z') || (c) == '_')
#define IDENT_WHOLE(c) (IDENT_START((c)) || ((c) >= '0' && (c) <= '9'))
#define NUMBER_START(c) ((c) >= '0' && (c) <= '9')
#define NUMBER_WHOLE(c) NUMBER_START((c))

enum LexerSource {
    LEXER_SOURCE_STR,
    LEXER_SOURCE_FILENAME,
};

struct Lexer {
    enum LexerSource source;
    char *str;
    size_t str_index;
    char *filename;
    FILE *file;
    bool eof;
    unsigned long index, line, column;
    int current;
    struct TokenVector *token_vector;
};

static void next_char(struct Lexer *lexer);
static const struct Token *get_token_eof(struct Lexer *lexer);
static const struct Token *get_token_ident(struct Lexer *lexer);
static const struct Token *get_token_number(struct Lexer *lexer);
static const struct Token *get_token_plus(struct Lexer *lexer);
static const struct Token *get_token_mul(struct Lexer *lexer);

struct Lexer *lexer_new_from_str(const char *const str)
{
    assert(str != NULL);

    struct Lexer *lexer = malloc(sizeof(struct Lexer));
    if (lexer == NULL) goto fail0;
    memset(lexer, 0, sizeof(struct Lexer));

    lexer->source = LEXER_SOURCE_STR;
    lexer->filename = NULL;
    lexer->file = NULL;

    const size_t str_size = strlen(str) + 1;

    lexer->str = malloc(str_size);
    if (lexer->str == NULL) goto fail1;
    strcpy(lexer->str, str);
    assert((strcmp(lexer->str, str) == 0));

    lexer->eof = false;
    lexer->index = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current = lexer->str[0];
    lexer->str_index = 0;

    lexer->token_vector = token_vector_new();
    if (lexer->token_vector == NULL) goto fail2;

    return lexer;

fail2:
    free(lexer->str);
fail1:
    free(lexer);
fail0:
    return NULL;
}

struct Lexer *lexer_new_from_filename(const char *const filename)
{
    assert(filename != NULL);

    struct Lexer *lexer = malloc(sizeof(struct Lexer));
    if (lexer == NULL) goto fail0;
    memset(lexer, 0, sizeof(struct Lexer));

    lexer->source = LEXER_SOURCE_FILENAME;
    lexer->str = NULL;
    lexer->str_index = 0;

    lexer->filename = malloc(strlen(filename) + 1);
    if (lexer->filename == NULL) goto fail1;
    strcpy(lexer->filename, filename);
    assert((strcmp(lexer->filename, filename) == 0));

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
    assert(lexer->token_vector != NULL);

    if (lexer->source == LEXER_SOURCE_STR) {
        assert(lexer->str != NULL);

        free(lexer->str);
    }
    else if (lexer->source == LEXER_SOURCE_FILENAME) {
        assert(lexer->filename != NULL);
        assert(lexer->file != NULL);

        fclose(lexer->file);
        free(lexer->filename);
    }
    else {
        assert(false);
    }

    token_vector_destroy(lexer->token_vector);
    free(lexer);
}

const struct Token *lexer_get_token(struct Lexer *const lexer)
{
    assert(lexer != NULL);

    while (lexer->current == ' ' || lexer->current == '\n') next_char(lexer);

    if (lexer->current == EOF) return get_token_eof(lexer);
    if (IDENT_START(lexer->current)) return get_token_ident(lexer);
    if (NUMBER_START(lexer->current)) return get_token_number(lexer);
    if (lexer->current == '+') return get_token_plus(lexer);
    if (lexer->current == '*') return get_token_mul(lexer);

    return NULL;
}

void next_char(struct Lexer *const lexer)
{
    if (lexer->current == '\n') {
        ++lexer->line;
        lexer->column = 1;
    }
    else {
        ++lexer->column;
    }

    ++lexer->index;

    if (lexer->source == LEXER_SOURCE_STR) {
        lexer->current = lexer->str[++lexer->str_index];

        if (lexer->current == '\0') {
            lexer->current = EOF;
        }
    }
    else if (lexer->source == LEXER_SOURCE_FILENAME) {
        lexer->current = fgetc(lexer->file);
    }
    else {
        assert(false);
    }
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

const struct Token *get_token_ident(struct Lexer *const lexer)
{
    const unsigned long index = lexer->index;
    const unsigned long line = lexer->line;
    const unsigned long column = lexer->column;

    char value[4096];
    memset(value, 0, sizeof(value));
    size_t idx = 0;

    while (IDENT_WHOLE(lexer->current)) {
        if (idx >= 4096) return NULL;
        value[idx++] = lexer->current;
        next_char(lexer);
    }

    return token_vector_append(
        lexer->token_vector,
        TOKEN_IDENT,
        index,
        line,
        column,
        value
    );
}

const struct Token *get_token_number(struct Lexer *const lexer)
{
    const unsigned long index = lexer->index;
    const unsigned long line = lexer->line;
    const unsigned long column = lexer->column;

    char value[4096];
    memset(value, 0, sizeof(value));
    size_t idx = 0;

    while (NUMBER_WHOLE(lexer->current)) {
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

const struct Token *get_token_plus(struct Lexer *const lexer)
{
    const struct Token *const token = token_vector_append(
        lexer->token_vector,
        TOKEN_PLUS,
        lexer->index,
        lexer->line,
        lexer->column,
        NULL
    );

    next_char(lexer);

    return token;
}

const struct Token *get_token_mul(struct Lexer *const lexer)
{
    const struct Token *const token = token_vector_append(
        lexer->token_vector,
        TOKEN_MUL,
        lexer->index,
        lexer->line,
        lexer->column,
        NULL
    );

    next_char(lexer);

    return token;
}
