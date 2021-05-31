#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED

#include "token.h"

#define LEXER_DESTROY(lexer) { lexer_destroy(lexer); lexer = NULL; }

struct Lexer *lexer_new_from_str(const char *str);
struct Lexer *lexer_new_from_filename(const char *filename);
void lexer_destroy(struct Lexer *lexer);
const struct Token *lexer_get_token(struct Lexer *lexer);

#endif // LEXER_INCLUDED
