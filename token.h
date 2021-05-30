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

void token_println(const struct Token *token);

#endif // TOKEN_INCLUDED
