#include "lexer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Lexer {
    char *filename;
};

struct Lexer *lexer_new_from_filename(const char *const filename)
{
    assert(filename != NULL);

    struct Lexer *lexer = malloc(sizeof(struct Lexer));
    memset(lexer, 0, sizeof(struct Lexer));

    lexer->filename = malloc(strlen(filename) + 1);
    if (lexer->filename == NULL) goto fail_after_lexer;
    strcpy(lexer->filename, filename);

    return lexer;

fail_after_lexer:
    free(lexer);
    return NULL;
}

void lexer_destroy(struct Lexer *const lexer)
{
    assert(lexer != NULL);

    if (lexer->filename) free(lexer->filename);
    free(lexer);
}
