#include "codegen.h"
#include <stdio.h>

CodeGen codegen;

static void emit_global_asm(char *name) {
    fprintf(codegen.out, "global %s\n", name);
}

static void emit_label_asm(char *name) {
    fprintf(codegen.out, "%s:\n", name);
}

static void emit_expression_asm(uint64_t value) {
    fprintf(codegen.out, "\tmov rax, %lu\n", value);
}

static void emit_return_asm() {
    fprintf(codegen.out, "\tret\n");
}

void generate_code(AstNode *code_node, char *outpath) {
    codegen.out = fopen(outpath, "w");
    if (!codegen.out) {
        printf("error: cannot open output file: %s\n", outpath);
        return;
    }

    emit_global_asm(func.name);
    emit_label_asm(func.name);
    emit_expression_asm(func.return_value);
    emit_return_asm();

    fclose(codegen.out);
}