#include "interpreter.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

Object interpreter_run(const struct Ast *const ast, const struct AstNode *const node)
{
    if (strcmp(node->type, "number") == 0) {
        if (node->token->type != TOKEN_NUMBER) return NAN;
        if (node->token->value == NULL) return NAN;
        return atof((const char*)node->token->value);
    }
    else if (strcmp(node->type, "add") == 0) {
        if (node->children_count == 0) return NAN;
        Object objects[node->children_count];
        for (size_t child_index = 0; child_index < node->children_count; ++child_index) {
            const size_t child_node_index = node->children[child_index];
            const struct AstNode *const child_node = ast_node_get(ast, child_node_index);
            objects[child_index] = interpreter_run(ast, child_node);
        }
        Object result = objects[0];
        for (size_t index = 1; index < node->children_count; ++index) {
            result = object_add(result, objects[index]);
        }
        return result;
    }
    else if (strcmp(node->type, "mul") == 0) {
        if (node->children_count == 0) return NAN;
        Object objects[node->children_count];
        for (size_t child_index = 0; child_index < node->children_count; ++child_index) {
            const size_t child_node_index = node->children[child_index];
            const struct AstNode *const child_node = ast_node_get(ast, child_node_index);
            objects[child_index] = interpreter_run(ast, child_node);
        }
        Object result = objects[0];
        for (size_t index = 1; index < node->children_count; ++index) {
            result = object_mul(result, objects[index]);
        }
        return result;
    }
    else {
        return NAN;
    }
}
