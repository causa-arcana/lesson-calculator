#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../src/ast.h"
#include "../src/token.h"

int main()
{
    struct Ast *ast = ast_new();
    assert(ast != NULL);

    struct TokenVector *token_vector = token_vector_new();
    assert(token_vector != NULL);

    assert(ast_nodes_count(ast) == 0);
    assert(ast_node_get(ast, 0) == NULL);
    assert(ast_node_get(ast, 1) == NULL);
    assert(ast_node_get(ast, 2) == NULL);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);

    const struct Token *const node0_token = token_vector_append(
        token_vector,
        TOKEN_NUMBER,
        0, 0, 0,
        "456"
    );
    const struct AstNode *const node0 = ast_node_create(ast, "foo", node0_token, 0, NULL);
    assert(node0 != NULL);
    assert(node0->used);
    assert(node0->ref_count == 0);
    assert(strcmp(node0->type, "foo") == 0);
    assert(node0->token == node0_token);
    assert(node0->children_count == 0);

    assert(ast_nodes_count(ast) == 1);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == NULL);
    assert(ast_node_get(ast, 2) == NULL);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);

    const struct Token *const node1_token = token_vector_append(
        token_vector,
        TOKEN_IDENT,
        0, 0, 0,
        "qwe"
    );
    const struct AstNode *const node1 = ast_node_create(ast, "bar", node1_token, 0, NULL);
    assert(node1 != NULL);
    assert(node1->used);
    assert(node1->ref_count == 0);
    assert(strcmp(node1->type, "bar") == 0);
    assert(node1->token == node1_token);
    assert(node1->children_count == 0);

    assert(ast_nodes_count(ast) == 2);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == NULL);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);

    const struct Token *const node2_token = token_vector_append(
        token_vector,
        TOKEN_PLUS,
        0, 0, 0,
        NULL
    );
    const size_t node2_children[2] = { 0, 1 };
    const struct AstNode *const node2 = ast_node_create(ast, "car", node2_token, 2, node2_children);
    assert(node2 != NULL);
    assert(node2->used);
    assert(node2->ref_count == 0);
    assert(strcmp(node2->type, "car") == 0);
    assert(node2->token == node2_token);
    assert(node2->children_count == 2);
    assert(node2->children[0] == 0);
    assert(node2->children[1] == 1);

    assert(ast_nodes_count(ast) == 3);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == node2);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 0)->ref_count == 1);
    assert(ast_node_get(ast, 1)->ref_count == 1);

    const struct Token *const node3_token = token_vector_append(
        token_vector,
        TOKEN_NUMBER,
        0, 0, 0,
        "123"
    );
    const struct AstNode *node3 = ast_node_create(ast, "cdr", node3_token, 0, NULL);
    assert(node3 != NULL);
    assert(node3->used);
    assert(node3->ref_count == 0);
    assert(strcmp(node3->type, "cdr") == 0);
    assert(node3->token == node3_token);
    assert(node3->children_count == 0);

    assert(ast_nodes_count(ast) == 4);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == node2);
    assert(ast_node_get(ast, 3) == node3);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 0)->ref_count == 1);
    assert(ast_node_get(ast, 1)->ref_count == 1);

    const struct Token *const node4_token = token_vector_append(
        token_vector,
        TOKEN_MUL,
        0, 0, 0,
        NULL
    );
    const size_t node5_children[2] = { 2, 3 };
    const struct AstNode *const node4 = ast_node_create(ast, "baz", node4_token, 2, node5_children);
    assert(node4 != NULL);
    assert(node4->used);
    assert(node4->ref_count == 0);
    assert(strcmp(node4->type, "baz") == 0);
    assert(node4->token == node4_token);
    assert(node4->children_count == 2);
    assert(node4->children[0] == 2);
    assert(node4->children[1] == 3);

    assert(ast_nodes_count(ast) == 5);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == node2);
    assert(ast_node_get(ast, 3) == node3);
    assert(ast_node_get(ast, 4) == node4);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 0)->ref_count == 1);
    assert(ast_node_get(ast, 1)->ref_count == 1);
    assert(ast_node_get(ast, 2)->ref_count == 1);
    assert(ast_node_get(ast, 3)->ref_count == 1);

    ast_node_println(ast, node4, 0);

    assert(!ast_node_destroy(ast, node0));
    assert(!ast_node_destroy(ast, node1));
    assert(!ast_node_destroy(ast, node2));
    assert(!ast_node_destroy(ast, node3));

    assert(ast_node_destroy(ast, node4));
    assert(ast_nodes_count(ast) == 4);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == node2);
    assert(ast_node_get(ast, 3) == node3);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 0)->ref_count == 1);
    assert(ast_node_get(ast, 1)->ref_count == 1);
    assert(ast_node_get(ast, 2)->ref_count == 0);
    assert(ast_node_get(ast, 3)->ref_count == 0);

    assert(!ast_node_destroy(ast, ast_node_get(ast, 0)));
    assert(!ast_node_destroy(ast, ast_node_get(ast, 1)));

    AST_NODE_DESTROY(ast, node3);
    assert(node3 == NULL);
    assert(ast_nodes_count(ast) == 3);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == node2);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 0)->ref_count == 1);
    assert(ast_node_get(ast, 1)->ref_count == 1);
    assert(ast_node_get(ast, 2)->ref_count == 0);

    assert(!ast_node_destroy(ast, ast_node_get(ast, 0)));
    assert(!ast_node_destroy(ast, ast_node_get(ast, 1)));

    assert(ast_node_destroy(ast, node2));
    assert(ast_nodes_count(ast) == 2);
    assert(ast_node_get(ast, 0) == node0);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == NULL);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 0)->ref_count == 0);
    assert(ast_node_get(ast, 1)->ref_count == 0);

    assert(ast_node_destroy(ast, node0));
    assert(ast_nodes_count(ast) == 1);
    assert(ast_node_get(ast, 0) == NULL);
    assert(ast_node_get(ast, 1) == node1);
    assert(ast_node_get(ast, 2) == NULL);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);
    assert(ast_node_get(ast, 1)->ref_count == 0);

    assert(ast_node_destroy(ast, node1));
    assert(ast_nodes_count(ast) == 0);
    assert(ast_node_get(ast, 0) == NULL);
    assert(ast_node_get(ast, 1) == NULL);
    assert(ast_node_get(ast, 2) == NULL);
    assert(ast_node_get(ast, 3) == NULL);
    assert(ast_node_get(ast, 4) == NULL);
    assert(ast_node_get(ast, 5) == NULL);

    AST_DESTROY(ast);
    assert(ast == NULL);

    TOKEN_VECTOR_DESTROY(token_vector);
    assert(token_vector == NULL);

    exit(EXIT_SUCCESS);
}
