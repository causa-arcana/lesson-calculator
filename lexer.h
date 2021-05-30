#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED

#define LEXER_DESTROY(lexer) { lexer_destroy(lexer); lexer = NULL; }

struct Lexer;

struct Lexer *lexer_new_from_filename(const char *filename);
void lexer_destroy(struct Lexer *lexer);

#endif // LEXER_INCLUDED
