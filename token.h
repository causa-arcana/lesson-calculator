#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED

#define TOKEN_VALUE_SIZE_MAX 1024

enum TokenType {
    TOKEN_EOF,
    TOKEN_NUMBER,
};

struct Token {
    enum TokenType type;
    unsigned long index, line, column, length;
    unsigned char value[TOKEN_VALUE_SIZE_MAX];
};

struct TokenVector *token_vector_new();
void token_vector_destroy(struct TokenVector *token_vector);
const struct Token *token_vector_append(
    struct TokenVector *token_vector,
    enum TokenType token_type,
    unsigned long index,
    unsigned long line,
    unsigned long column,
    const char *value
);

void token_println(const struct Token *token);

#endif // TOKEN_INCLUDED
