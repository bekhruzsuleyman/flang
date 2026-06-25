#include "parser.h"
#include "lexer.h"
#include "builtin_funcs.h"
#include "ast.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codegen.h"

static Token current;
static char *outpath;

AstNode *root_node;
AstNode *head_node;

static void advance(void) {
    current = lexer_next();
}

static Token expect(TokenKind expected, ErrorStructure error) {
    if (current.kind != expected) {
        raise_error(error); // Stops and quits Compiler
    }
    Token current_saved = current;

    advance();
    return current_saved; 
}

static bool peek(TokenKind token_kind) {
    if (current.kind == token_kind) {
        return true;
    } else {
        return false;
    }
}

static void skip_newlines(void) {
    while (current.kind == TOK_NEWLINE) advance();
}

static void set_ast_node(AstNode *new_ast_node, AstNode **body) {
    (*body)->next = new_ast_node;
    new_ast_node->next = NULL; 
    *body = new_ast_node; 
}

static AstNode *new_ast_node(AstKind kind) {
    AstNode *node = malloc(sizeof(AstNode));
    if (!node) raise_error(errorMemory);

    memset(node, 0, sizeof(AstNode));
    node->kind = kind;
    node->next = NULL;
    return node;
}

static void function_add_stmt(AstNode *func, AstNode *stmt) {
    stmt->next = NULL;

    if (!func->function.body_head) {
        func->function.body_head = stmt;
        func->function.body_tail = stmt;
    } else {
        func->function.body_tail->next = stmt;
        func->function.body_tail = stmt;
    }
}

static AstNode *parse_return(void) {
    AstNode *stmt = new_ast_node(AST_RETURN);

    expect(TOK_RETURN, errorSyntax);

    Token ret_value = expect(TOK_INT, errorType);

    AstNode *value = new_ast_node(AST_U64_LIT);
    value->u64_lit.value = ret_value.num;

    stmt->return_stmt.value = value;

    return stmt;
}

static void parse_function() {
    AstNode *function_ast = new_ast_node(AST_FUNCTION);

    // Start
    expect(TOK_FN, errorFunc);
    Token func_name = expect(TOK_IDENT, errorIdent);
    strncpy(function_ast->function.name, func_name.text, 63);
    
    expect(TOK_LPAREN, errorSyntax);
    expect(TOK_RPAREN, errorSyntax);
    
    expect(TOK_ARROW, errorSyntax);
    Token func_type = expect(TOK_TYPE, errorType);
    strncpy(function_ast->function.return_type, func_type.text, 63);
    
    // Body
    expect(TOK_LBRACE, errorSyntax);

    function_ast->function.body_head = NULL;
    function_ast->function.body_tail = NULL;
    
    skip_newlines();
    while (!peek(TOK_RBRACE) && !peek(TOK_EOF)) {
        if (peek(TOK_RETURN)) {
            AstNode *stmt = parse_return();
            function_add_stmt(function_ast, stmt);
        } else {
            raise_error(errorSyntax);
        }

        skip_newlines();
    }

    skip_newlines();

    // End
    expect(TOK_RBRACE, errorSyntax);

    function_ast->function.name[63] = '\0';
    function_ast->function.return_type[63] = '\0';

    printf("Function: %s\n", function_ast->function.name);
    printf("Type: %s\n", function_ast->function.return_type);
    printf("Value: %lu\n", function_ast->function.body_tail->return_stmt.value->u64_lit.value);

    set_ast_node(function_ast, &head_node);
}

void parser_parse(void) {
    while (!peek(TOK_EOF)) {
        skip_newlines();

        if (peek(TOK_FN)) {
            parse_function();
        } else raise_error(errorSyntax);
    }
}

void parser_init(char *source, char *outpath_new) {
    lexer_init(source);
    current = lexer_next();
    outpath = outpath_new;
    root_node = new_ast_node(AST_CODE);

    head_node = root_node;
    parser_parse();
}
