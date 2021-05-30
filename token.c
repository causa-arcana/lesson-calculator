#include "token.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

static const char *token_type_str(enum TokenType token_type);

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
