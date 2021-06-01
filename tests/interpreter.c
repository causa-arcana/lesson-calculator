#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "../src/ast.h"
#include "../src/interpreter.h"
#include "../src/object.h"
#include "../src/token.h"

int main()
{
    struct Ast *ast = ast_new();
    assert(ast != NULL);

    struct TokenVector *token_vector = token_vector_new();
    assert(token_vector != NULL);

    const struct Token *const node0_token = token_vector_append(
        token_vector,
        TOKEN_NUMBER,
        0, 0, 0,
        "2"
    );

    __attribute__((unused)) const struct AstNode *const node0 =
        ast_node_create(ast, "number", node0_token, 0, NULL);

    const struct Token *const node1_token = token_vector_append(
        token_vector,
        TOKEN_NUMBER,
        0, 0, 0,
        "3"
    );

    __attribute__((unused)) const struct AstNode *const node1 =
        ast_node_create(ast, "number", node1_token, 0, NULL);

    const struct Token *const node2_token = token_vector_append(
        token_vector,
        TOKEN_PLUS,
        0, 0, 0,
        NULL
    );

    const size_t node2_children[2] = { 0, 1 };

    const struct AstNode *const node2 =
        ast_node_create(ast, "add", node2_token, 2, node2_children);

    assert(fabs(interpreter_run(ast, node2) - 5.0) < 0.000000001);

    const struct Token *const node3_token = token_vector_append(
        token_vector,
        TOKEN_NUMBER,
        0, 0, 0,
        "5"
    );

    __attribute__((unused)) const struct AstNode *const node3 =
        ast_node_create(ast, "number", node3_token, 0, NULL);

    const struct Token *const node4_token = token_vector_append(
        token_vector,
        TOKEN_MUL,
        0, 0, 0,
        NULL
    );

    const size_t node4_children[2] = { 2, 3 };

    const struct AstNode *const node4 =
        ast_node_create(ast, "mul", node4_token, 2, node4_children);

    assert(fabs(interpreter_run(ast, node4) - 25.0) < 0.000000001);

    AST_DESTROY(ast);
    TOKEN_VECTOR_DESTROY(token_vector);

    exit(EXIT_SUCCESS);
}
