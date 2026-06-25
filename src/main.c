#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

char *read_file(const char *path) {
    FILE *file = fopen(path, "rb");

    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char **argv) {
    char *input_file = NULL;
    char *output_file = "a.out";

    if (argc < 2) {
        printf("usage: flang <input> -o <output>\n");
        return 1;
    }

    input_file = argv[1];

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                printf("error: -o needs output filename\n");
                return 1;
            }

            output_file = argv[i + 1];
            i++;
        } else {
            printf("unknown argument: %s\n", argv[i]);
            return 1;
        }
    }

    printf("input: %s\n", input_file);
    printf("output: %s\n", output_file);

    char *source = read_file(input_file);

    if (!source) {
        printf("Could not open '%s'\n", argv[1]);
        return 1;
    }

    lexer_init(source);

    while (1) {
        Token token = lexer_next();

        printf("%s", token_name(token.kind));

        if (token.kind == TOK_IDENT || token.kind == TOK_TYPE) {
            printf("(%s)", token.text);
        }

        if (token.kind == TOK_INT) {
            printf("(%lu)", token.num);
        }

        printf("\n");

        if (token.kind == TOK_EOF) break;
    }

    parser_init(source, output_file);
    
    free(source);
    return 0;
}