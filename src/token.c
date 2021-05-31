#include "token.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TokenVector {
    size_t capacity;
    size_t count;
    struct Token *ptr;
};

static const char *token_type_str(enum TokenType token_type);

struct TokenVector *token_vector_new()
{
    struct TokenVector *const token_vector = malloc(sizeof(struct TokenVector));
    if (token_vector == NULL) goto fail0;
    memset(token_vector, 0, sizeof(struct TokenVector));

    token_vector->capacity = 1000;
    token_vector->count = 0;

    token_vector->ptr = malloc(1000 * sizeof(struct Token));
    if (token_vector->ptr == NULL) goto fail1;
    memset(token_vector->ptr, 0, 1000 * sizeof(struct Token));

    return token_vector;

fail1:
    free(token_vector);
fail0:
    return NULL;
}

void token_vector_destroy(struct TokenVector *const token_vector)
{
    assert(token_vector != NULL);
    assert(token_vector->ptr != NULL);

    free(token_vector->ptr);
    free(token_vector);
}

const struct Token *token_vector_append(
    struct TokenVector *token_vector,
    enum TokenType token_type,
    unsigned long index,
    unsigned long line,
    unsigned long column,
    const char *value
) {
    assert(token_vector != NULL);
    assert(token_vector->ptr != NULL);
    assert(token_vector->capacity > 0);
    assert(token_vector->count <= token_vector->capacity);

    if (token_vector->count == token_vector->capacity) {
        if (token_vector->capacity >= 1000000) return NULL;

        const size_t capacity = token_vector->capacity + 1000;

        struct Token *ptr = realloc(token_vector->ptr, capacity * sizeof(struct Token));
        if (ptr == NULL) return NULL;
        memset(&ptr[token_vector->capacity], 0, 1000 * sizeof(struct Token));

        token_vector->ptr = ptr;
        token_vector->capacity = capacity;
    }

    const size_t length = value == NULL ? 0 : strlen(value);

    if (length > TOKEN_VALUE_SIZE_MAX - 1) return NULL;

    token_vector->ptr[token_vector->count].type = token_type;
    token_vector->ptr[token_vector->count].index = index;
    token_vector->ptr[token_vector->count].line = line;
    token_vector->ptr[token_vector->count].column = column;
    token_vector->ptr[token_vector->count].length = length;
    if (value != NULL) {
        strcpy((char*)token_vector->ptr[token_vector->count].value, value);
    }

    return &token_vector->ptr[token_vector->count++];
}

void token_println(const struct Token *const token)
{
    printf(
        "%s:%lu:%lu:%lu:%s\n",
        token_type_str(token->type),
        token->index,
        token->line,
        token->column,
        token->value[0] == '\0' ? "NULL" : ((char*)token->value)
    );
}

const char *token_type_str(const enum TokenType token_type)
{
    switch (token_type) {
    case TOKEN_EOF: return "EOF";
    case TOKEN_IDENT: return "IDENT";
    case TOKEN_NUMBER: return "NUMBER";
    default: assert(false);
    }
}
