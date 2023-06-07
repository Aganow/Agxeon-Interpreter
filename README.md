# Agxeon-Interpreter

This is a simple interpreter script written in C. It interprets and executes a program written in a custom stack-based language.

## Features

- Performs basic arithmetic operations (`+`, `-`, `*`, `/`) on a stack.
- Handles integer values and outputs the result (`n` instruction).
- Supports reading the program code from a file.

## Usage

To use the interpreter, follow these steps:

Compile the script using a C compiler:

   ```bash
   gcc interpreter.c -o interpreter
   ```

## Program Language

The interpreter reads a program file that contains instructions written in a simple stack-based language. Each instruction is represented by a single character:

- `+`: Addition
- `-`: Subtraction
- `*`: Multiplication
- `/`: Division
- `n`: Output the top value of the stack

Any other character that is a digit (`0` to `9`) will be treated as a number and pushed onto the stack.

## License

This script is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it according to your needs.
