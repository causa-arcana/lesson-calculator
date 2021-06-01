#ifndef INTERPRETER_INCLUDED
#define INTERPRETER_INCLUDED

#include "ast.h"
#include "object.h"

Object interpreter_run(const struct Ast *ast, const struct AstNode *node);

#endif // INTERPRETER_INCLUDED
