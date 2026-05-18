*this project has been made as part of 42 curriculum by ethutin-, apolleux*

# Minishell

## Description

Minishell is a simplified Unix shell developed as part of the 42 curriculum.
The goal of this project is to recreate the behavior of a basic shell by handling command parsing, execution, pipes, and redirections.

This project focuses on understanding:

* process creation and management
* file descriptors and redirections
* parsing and tokenization
* environment variables handling

---

## Instruction

### Compilation

```bash
make
```

### Execution

```bash
./minishell
```

---

### Features

* Execution of simple commands
* Pipes (`|`)
* Input and output redirections (`<`, `>`, `>>`, `<<`)
* Environment variables
* Signal handling (Ctrl+C, Ctrl+D, Ctrl+)
* Builtins:

    * `echo`
    * `cd`
    * `pwd`
    * `export`
    * `unset`
    * `env`
    * `exit`

---

### Project Architecture

```text
input
  ↓
lexer (tokenizer)
  ↓
parser (commands struct)
  ↓
executor
```

#### Lexer

Transforms the input string into a list of tokens.

#### Parser

Organizes tokens into command structures.

#### Executor

Executes commands using fork, execve, and pipes.

---

## Resources

### Documentation

* https://man7.org/linux/man-pages/
* https://pubs.opengroup.org/onlinepubs/9699919799/

### Useful Concepts

* `fork`, `execve`, `wait`
* file descriptors (`dup2`)
* signals (`signal`, `sigaction`)
* parsing strategies
---
