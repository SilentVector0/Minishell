*This project has been created as part of the 42 curriculum by aroduit, msuter.*

# Minishell

## Description

Minishell is a lightweight Unix shell implemented in C, developed as part of the 42 school curriculum. The goal of the project is to recreate a functional shell inspired by bash, capable of interpreting and executing commands in an interactive environment.

The shell handles the following features:

- Interactive prompt with command history
- Executable resolution via `PATH`, relative, or absolute paths
- Single quotes `'` — prevents interpretation of all metacharacters
- Double quotes `"` — prevents interpretation of metacharacters except `$`
- Environment variable expansion (`$VAR`, `$?`)
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Pipes `|` — chaining commands via pipeline
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\`
- Syntax error detection and reporting
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Instructions

### Compilation

```bash
make
```

This will compile the libft, all source files, and produce the `minishell` executable.

### Execution

```bash
./minishell
```

### Makefile rules

| Rule | Description |
|---|---|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executable |
| `make re` | Recompile from scratch |

## Architecture

```
.
├── sources/
│   ├── main/          # Entry point, signal handling, SHLVL, syntax validation
│   ├── all_lexer/     # Tokenization (lexer)
│   ├── all_parser/    # Parsing into command structures
│   ├── all_expander/  # Variable expansion
│   ├── all_exec/      # Execution, redirections, heredoc, pipes
│   └── builtin/       # Built-in commands
├── libft/             # Custom C library
└── Makefile
```

## Resources

- [readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html) — for interactive prompt and history management
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgramming/c8-io-redir-pipes.pdf) — overview of shell architecture, pipes, and redirections
- [42 Minishell tester by LucasKuhn](https://github.com/LucasKuhn/minishell_tester) — community test suite used for validation

### AI Usage

Claude (Anthropic) was used during the final stages of the project for:

- **Testing** — generating edge case test suites covering syntax errors, quote handling, redirections, pipes, and built-in commands
- **Debugging** — identifying issues in syntax validation logic (`verif_syntax`) and quote detection, analyzing segfaults caused by unclosed quotes reaching the lexer