#include "ast.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Ast {
    size_t capacity;
    struct AstNode *nodes;
};

struct Ast *ast_new()
{
    struct Ast *const ast = malloc(sizeof(struct Ast));
    if (ast == NULL) goto fail0;
    memset(ast, 0, sizeof(struct Ast));

    ast->capacity = 1000;

    ast->nodes = malloc(ast->capacity * sizeof(struct AstNode));
    if (ast->nodes == NULL) goto fail1;
    memset(ast->nodes, 0, ast->capacity * sizeof(struct AstNode));

    for (size_t index = 0; index < ast->capacity; ++index) {
        ast->nodes[index].used = false;
        ast->nodes[index].ref_count = 0;
    }

    return ast;

fail1:
    free(ast);
fail0:
    return NULL;
}

void ast_destroy(struct Ast *const ast)
{
    assert(ast != NULL);
    assert(ast->capacity > 0);
    assert(ast->nodes != NULL);

    free(ast->nodes);
    free(ast);
}

size_t ast_nodes_count(const struct Ast *const ast)
{
    assert(ast != NULL);
    assert(ast->capacity > 0);
    assert(ast->nodes != NULL);

    size_t count = 0;

    for (size_t index = 0; index < ast->capacity; ++index) {
        if (ast->nodes[index].used) ++count;
    }

    return count;
}

const struct AstNode *ast_node_get(const struct Ast *const ast, size_t index)
{
    assert(ast != NULL);
    assert(ast->capacity > 0);
    assert(ast->nodes != NULL);
    assert(index < ast->capacity);

    const struct AstNode *const node = &ast->nodes[index];

    return node->used ? node : NULL;
}

const struct AstNode *ast_node_create(
    struct Ast *const ast,
    const char *const type,
    const struct Token *const token,
    const size_t children_count,
    const size_t children[]
) {
    assert(ast != NULL);
    assert(ast->capacity > 0);
    assert(ast->nodes != NULL);
    assert(type != NULL);
    assert(type[0] != '\0');
    assert(children_count <= AST_NODE_CHILDREN_COUNT_MAX);
    if (children_count > 0) assert(children != NULL);

    size_t new_index = ast->capacity;

    for (size_t index = 0; index < ast->capacity; ++index) {
        if (!ast->nodes[index].used) {
            new_index = index;
            break;
        }
    }

    if (new_index == ast->capacity) {
        if (ast->capacity >= 100000) return NULL;

        const size_t capacity = ast->capacity + 1000;

        struct AstNode *const nodes = realloc(ast->nodes, capacity * sizeof(struct AstNode));
        if (nodes == NULL) return NULL;
        memset(&nodes[ast->capacity], 0, 1000 * sizeof(struct AstNode));
        for (size_t index = capacity - 1000; index < capacity; ++index) {
            nodes[index].used = false;
        }

        ast->nodes = nodes;
        ast->capacity = capacity;
    }

    ast->nodes[new_index].ref_count = 0;
    strcpy(ast->nodes[new_index].type, type);
    ast->nodes[new_index].token = token;
    ast->nodes[new_index].children_count = children_count;

    for (size_t index = 0; index < children_count; ++index) {
        ast->nodes[new_index].children[index] = children[index];
    }

    ast->nodes[new_index].used = true;

    return &ast->nodes[new_index];
}
