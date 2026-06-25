#pragma once

#include <stdint.h>

typedef enum {
    TOK_EOF,
    TOK_FN,
    TOK_VAR,
    TOK_RETURN,
    TOK_IDENT,
    TOK_INT,
    TOK_TYPE,
    TOK_LPAREN, TOK_RPAREN,
    TOK_LBRACE, TOK_RBRACE,
    TOK_EQUAL,
    TOK_MINUS,
    TOK_ARROW,
    TOK_SEMI,
    TOK_NEWLINE,
    TOK_UNKNOWN
} TokenKind;

typedef struct {
    TokenKind kind;
    char text[64];
    uint64_t num;
} Token;