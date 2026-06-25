#pragma once

#include <stdio.h>


typedef struct {
    char *type;
    char *message;
} ErrorStructure;

extern ErrorStructure errorIdent;
extern ErrorStructure errorColon;
extern ErrorStructure errorEqual;
extern ErrorStructure errorNewline;
extern ErrorStructure errorType;
extern ErrorStructure errorVarValueType;
extern ErrorStructure errorVarLimit;
extern ErrorStructure errorFunc;
extern ErrorStructure errorSyntax;
extern ErrorStructure errorMemory;

void raise_error(ErrorStructure error);
