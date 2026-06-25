#pragma once

#include "ast.h"
#include <stdio.h>

typedef struct {
    FILE *out;
} CodeGen;

void generate_code(AstNode *code_node, char *outpath); // generating only functions for now!