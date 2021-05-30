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

void token_println(const struct Token *const token)
{
    printf(
        "Token:%s:%lu:%lu:%lu:%s\n",
        token_type_str(token->type),
        token->index,
        token->line,
        token->column,
        token->value
    );
}

const char *token_type_str(const enum TokenType token_type)
{
    switch (token_type) {
    case TOKEN_EOF: return "EOF";
    default: assert(false);
    }
}
