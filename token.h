#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED

#define TOKEN_VALUE_LENGTH_MAX 1024

enum TokenType {
    TOKEN_EOF,
};

struct Token {
    enum TokenType type;
    unsigned long index, line, column, length;
    unsigned char value[TOKEN_VALUE_LENGTH_MAX];
};

struct TokenVector *token_vector_new();
void token_vector_destroy(struct TokenVector *token_vector);

void token_println(const struct Token *token);

#endif // TOKEN_INCLUDED
