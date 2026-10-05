# flang (early prototype)

> **This is an early prototype, superseded by [flang-lite](https://github.com/bekhruzsuleyman/flang-lite).** It is incomplete and no longer developed. It is kept here for history. For the maintained language, see flang-lite.

flang was a first attempt at a small compiled language written in C, with the goal of compiling functions to x86-64 assembly that C programs could call.

## What it implements

- **Lexer** (`src/lexer.c`): keywords `fn`, `var`, `return`; type names `u64`, `int`, `char`, `boolean`, `string`; identifiers; unsigned integer literals; `( ) { } = ; -` and `->`; newlines as tokens.
- **Parser** (`src/parser.c`, `src/ast.h`): parses one or more functions of the form

  ```
  fn name() -> u64 {
      return 123
  }
  ```

  into a linked-list AST. Function bodies may only contain `return <integer>` statements. There are no parameters, variables or expressions yet (`var` is lexed but not parsed). Syntax errors are reported as `[Kind]: message` and stop the program.
- **Code generation** (`src/codegen.cs`): an unfinished sketch of an assembly emitter. It is not part of the build (the Makefile compiles only `src/*.c`) and would not compile as-is. **No assembly is generated.** `examples/example1.asm` and `examples/example_c_usage.c` show the intended output and how C code would call it; they are not produced by this compiler.

## Build and run

Requires `gcc` and `make`. The Makefile builds with `-g -fsanitize=address`.

```sh
make
./flang examples/example1.f -o example1.asm
```

The compiler prints the token stream, then a summary of each parsed function. Real output:

```
input: examples/example1.f
output: example1.asm
FN
IDENT(number)
LPAREN
RPAREN
ARROW
TYPE(u64)
LBRACE
NEWLINE
RETURN
INT(123123)
NEWLINE
RETURN
INT(123122)
NEWLINE
RBRACE
EOF
Function: number
Type: u64
Value: 123122
```

`Value` is the last `return` in the body. The `-o` option is accepted, but no output file is written.

## License

MIT. See [LICENSE](LICENSE).
