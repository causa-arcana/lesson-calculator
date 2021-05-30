#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_DESTROY(lexer) { lexer_destroy(lexer); lexer = NULL; }

struct Lexer;

struct Lexer *lexer_new_from_filename(const char *filename);
void lexer_destroy(struct Lexer *lexer);

struct Lexer {
    char *filename;
};

int main(const int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "No input files\n");
        exit(EXIT_FAILURE);
    }

    const char *const filename = argv[1];

    struct Lexer *lexer = lexer_new_from_filename(filename);

    if (lexer) {
        LEXER_DESTROY(lexer);
    }

    exit(EXIT_SUCCESS);
}

struct Lexer *lexer_new_from_filename(const char *const filename)
{
    if (filename == NULL) return NULL;

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
