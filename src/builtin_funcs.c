#include "builtin_funcs.h"
#include <stdlib.h>

ErrorStructure errorIdent = {"NameError", "Wrong variable name!"};
ErrorStructure errorColon = {"SyntaxError", "Missing Colon!"};
ErrorStructure errorEqual = {"SyntaxError", "Missing Equal!"};
ErrorStructure errorFunc = {"SyntaxError", "Wrong function usage!"};
ErrorStructure errorNewline = {"SyntaxError", "Missing Newline!"};
ErrorStructure errorType = {"TypeError", "Type mismatch!"};
ErrorStructure errorVarValueType = {"TypeError", "Variable value type mismatch!"};
ErrorStructure errorVarLimit = {"VariableLimit", "You exceed from variable limit (100)!"};
ErrorStructure errorSyntax = {"SyntaxError", "Syntax Error"};
ErrorStructure errorMemory = {"MemoryFull", "Out of memory!"};

void raise_error(ErrorStructure error) {
    fprintf(stderr, "[%s]: %s\n", error.type, error.message);
    exit(1);
}