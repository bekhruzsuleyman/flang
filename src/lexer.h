#pragma once

#include "token.h"

char *token_name(TokenKind token_kind);
void lexer_init(char *src);
Token lexer_next(void);