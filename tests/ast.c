#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../src/ast.h"

int main()
{
    struct Ast *ast = ast_new();
    assert(ast != NULL);

    assert(ast_nodes_count(ast) == 0);
    assert(ast_node_get(ast, 0) == NULL);
    assert(ast_node_get(ast, 1) == NULL);
    assert(ast_node_get(ast, 2) == NULL);

    const struct AstNode *const node0 = ast_node_create(ast, "foo", NULL, 0, NULL);
    assert(node0 != NULL);
    assert(node0->used);
    assert(strcmp(node0->type, "foo") == 0);
    assert(node0->token == NULL);
    assert(node0->children_count == 0);

    assert(ast_nodes_count(ast) == 1);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == NULL);
    assert(ast_node_get(ast, 2) == NULL);

    const struct AstNode *const node1 = ast_node_create(ast, "bar", NULL, 0, NULL);
    assert(node1 != NULL);
    assert(node1->used);
    assert(strcmp(node1->type, "bar") == 0);
    assert(node1->token == NULL);
    assert(node1->children_count == 0);

    assert(ast_nodes_count(ast) == 2);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == NULL);

    AST_DESTROY(ast);
    assert(ast == NULL);

    exit(EXIT_SUCCESS);
}
