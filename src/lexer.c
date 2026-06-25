#include "lexer.h"
#include <string.h>
#include <ctype.h>

static char *source;
static uint64_t pos = 0;

static char peek(void) {
    return source[pos];
}

// static char peek_next(void) {
//     if (source[pos] != '\0') {
//         return source[pos + 1];
//     } else {
//         return '\0';
//     }
// }

char *token_name(TokenKind token_kind) {
    switch (token_kind) {
        case TOK_EOF: return "EOF";
        case TOK_FN: return "FN";
        case TOK_VAR: return "VAR";
        case TOK_ARROW: return "ARROW";
        case TOK_IDENT: return "IDENT";
        case TOK_TYPE: return "TYPE";
        case TOK_LBRACE: return "LBRACE";
        case TOK_RBRACE: return "RBRACE";
        case TOK_LPAREN: return "LPAREN";
        case TOK_RPAREN: return "RPAREN";
        case TOK_EQUAL: return "EQUAL";
        case TOK_RETURN: return "RETURN";
        case TOK_INT: return "INT";
        case TOK_SEMI: return "SEMI";
        case TOK_NEWLINE: return "NEWLINE";
        case TOK_MINUS: return "MINUS";
        case TOK_UNKNOWN: return "UNKNOWN";
    }
    return "UNKNOWN";
}

static char advance(void) {
    return source[pos++];
}

void lexer_init(char *src) {
    source = src;
    pos = 0;
}

Token lexer_next(void) {
    Token token; 
    memset(&token, 0, sizeof(Token));

    while (1) {
        char current = peek();

        if (current == ' ' || current == '\t' || current == '\r') {
            advance();
            continue;
        }

        if (current == '\n') {
            token.kind = TOK_NEWLINE;
            advance();
            return token;
        }

        break;
    }
    
    if (peek() == '\0') {
        token.kind = TOK_EOF;
        return token;
    }

    if (isalpha((unsigned char) peek()) || peek() == '_') {
        uint8_t i = 0;

        while (isalnum((unsigned char) peek()) || peek() == '_'){
            if (i < 63) token.text[i++] = advance();
            else advance();
        }

        token.text[i] = '\0';

        if (strcmp(token.text, "fn") == 0) token.kind = TOK_FN;
        else if (strcmp(token.text, "return") == 0) token.kind = TOK_RETURN;
        else if (strcmp(token.text, "var") == 0) token.kind = TOK_VAR;
        else if (strcmp(token.text, "u64") == 0
                || strcmp(token.text, "int") == 0
                || strcmp(token.text, "char") == 0
                || strcmp(token.text, "boolean") == 0
                || strcmp(token.text, "string") == 0) token.kind = TOK_TYPE;
        else token.kind = TOK_IDENT;

        return token;
    }

    if (isdigit((unsigned char)peek())) {
        uint64_t value = 0;
        while (isdigit((unsigned char)peek())) {
            value = value * 10 + (advance() - '0');
        }

        token.kind = TOK_INT;
        token.num = value;
        return token;
    }

    char c = advance();

    switch (c) {
        case '(': token.kind = TOK_LPAREN; break;
        case ')': token.kind = TOK_RPAREN; break;
        case '{': token.kind = TOK_LBRACE; break;
        case '}': token.kind = TOK_RBRACE; break;
        case ';': token.kind = TOK_SEMI; break;
        case '=': token.kind = TOK_EQUAL; break;
        case '-':
            if (peek() == '>') {
                advance();
                token.kind = TOK_ARROW;
            } else token.kind = TOK_MINUS;
            break;
        default: token.kind = TOK_UNKNOWN; break;
    }

    return token;
}