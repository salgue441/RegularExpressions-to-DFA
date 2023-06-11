# Regular expression to DFA Converter

This project is a Regular Expression to Deterministic Finite Automaton (DFA) Converter implemented in modern C++. It allows you to convert regular expressions into their equivalent DFAs, enabling you to perform pattern matching and recognition efficiently.

## Features

- Conversion of regular expressions to DFAs
- Support for basic regular expression operators such as concatenation, union (OR),
  Kleene star (closure), and parentheses (zero or more occurrences)
- Handles parentheses to enfore precedence and grouping of expressions
- Supports a variety of input symbols, including alphabets, digits, special characters,
  and whitespace
- Graphical visualization of the generated DFA using OpenGL and Glew

## Requirements

To build and run the Regular Expression to DFA Converter, you will need the following:

- C++ compiler with C++17 support (e.g. GCC 7.0+)
- CMake 3.10+
- OpenGL 3.3+
- Glew 2.1.0+

## Running the Converter

To run the converter, you can use the following commands:

```bash
./run.sh
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
