#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../src/lexer.h"

int main()
{
    struct Lexer *lexer = lexer_new_from_filename("examples/foo.txt");
    assert(lexer != NULL);

    {
        const struct Token *token = lexer_get_token(lexer);
        assert(token != NULL);
        assert(token->type == TOKEN_IDENT);
        assert(token->index == 0);
        assert(token->line == 1);
        assert(token->column == 1);
        assert(strcmp((const char*)token->value, "foo") == 0);
    }

    {
        const struct Token *token = lexer_get_token(lexer);
        assert(token != NULL);
        assert(token->type == TOKEN_NUMBER);
        assert(token->index == 4);
        assert(token->line == 1);
        assert(token->column == 5);
        assert(strcmp((const char*)token->value, "123") == 0);
    }

    {
        const struct Token *token = lexer_get_token(lexer);
        assert(token != NULL);
        assert(token->type == TOKEN_IDENT);
        assert(token->index == 8);
        assert(token->line == 1);
        assert(token->column == 9);
        assert(strcmp((const char*)token->value, "bar9") == 0);
    }

    {
        const struct Token *token = lexer_get_token(lexer);
        assert(token != NULL);
        assert(token->type == TOKEN_NUMBER);
        assert(token->index == 13);
        assert(token->line == 1);
        assert(token->column == 14);
        assert(strcmp((const char*)token->value, "456") == 0);
    }

    {
        const struct Token *token = lexer_get_token(lexer);
        assert(token != NULL);
        assert(token->type == TOKEN_EOF);
        assert(token->index == 17);
        assert(token->line == 2);
        assert(token->column == 1);
        assert(strcmp((const char*)token->value, "") == 0);
    }

    assert(lexer_get_token(lexer) == NULL);
    assert(lexer_get_token(lexer) == NULL);

    LEXER_DESTROY(lexer);
    assert(lexer == NULL);

    exit(EXIT_SUCCESS);
}
