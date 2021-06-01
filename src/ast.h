#ifndef AST_INCLUDED
#define AST_INCLUDED

#include "token.h"

#include <stdbool.h>
#include <stdlib.h>

#define AST_DESTROY(ast) { ast_destroy(ast); ast = NULL; }
#define AST_NODE_DESTROY(ast, node) { if (ast_node_destroy(ast, node)) node = NULL; }
#define AST_NODE_TYPE_SIZE_MAX 128
#define AST_NODE_CHILDREN_COUNT_MAX 1024

struct AstNode {
    bool used;
    size_t ref_count;
    char type[AST_NODE_TYPE_SIZE_MAX];
    const struct Token *token;
    size_t children_count;
    size_t children[AST_NODE_CHILDREN_COUNT_MAX];
};

struct Ast *ast_new();
void ast_destroy(struct Ast *ast);

size_t ast_nodes_count(const struct Ast *ast);
const struct AstNode *ast_node_get(const struct Ast *ast, size_t index);

const struct AstNode *ast_node_create(
    struct Ast *ast,
    const char *type,
    const struct Token *token,
    size_t children_count,
    const size_t children[]
);
bool ast_node_destroy(struct Ast *ast, const struct AstNode *node);

#endif // AST_INCLUDED
