#pragma once

#include <stdint.h>

typedef enum {
    AST_CODE,
    AST_FUNCTION,
    AST_RETURN,
    AST_VARIABLE,
    AST_U64_LIT
} AstKind;

typedef struct AstNode AstNode;

struct AstNode {
    AstKind kind;
    AstNode *next;

    union {
        struct {
            char name[64];
            char return_type[64];
            AstNode *body_head;
            AstNode *body_tail;
        } function;

        struct {
            char name[64];
            char type[64];
            AstNode *value;
            int stack_offset;
        } variable;

        struct {
            AstNode *value;
        } return_stmt;

        struct {
            uint64_t value;
        } u64_lit;
    };
};
