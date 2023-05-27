# Regular Expressions to DFA

## Title of the project

### University

Instituto Tecnológico de Estudios Superiores de Monterrey, Campus Querétaro

### Course

Implementación de Métodos Computacionales.

| Semester | Teacher     |
| -------- | ----------- |
| 2023-01  | Pedro Perez |

### Authors

| Name            | Student ID | GitHub Username                                     |
| --------------- | ---------- | --------------------------------------------------- |
| Carlos Salguero | A00833341  | [carlos-salguero](https://github.com/salgue441)     |
| Diego Sandoval  | A0170      | [DiegoSandovalV](https://github.com/DiegoSandovalV) |

## Table of Contents

## Introduction

This project is an implementation of a regular expression to DFA converter. It is written in
modern C++ and uses the [Boost](https://www.boost.org/) library for its regular expression
parser. The project is built using [CMake](https://cmake.org/).

Uses the [Thompson's Construction](https://en.wikipedia.org/wiki/Thompson%27s_construction)
algorithm to convert the regular expression to a non-deterministic finite automaton (NFA).
The NFA is then converted to a DFA using the [Subset Construction](https://en.wikipedia.org/wiki/Powerset_construction)

The output of the program is a [Graphviz](https://graphviz.org/) DOT file. The format
of the output is an adjacency list representation of the DFA. This can be
converted to an image using the `dot` command line tool.

```bash
dot -Tpng -o output.png output.dot
```

## Building

To build the project, you will need to have CMake installed. You can then run the following
commands to build the project:

```bash
./run.sh
```

This will create an executable called `regex2dfa` in the `build` directory.

## Usage

The program takes a single argument, which is the regular expression within a file
that you want to convert to a DFA. The program will then output the DFA to stdout.

```bash
./regex2dfa <regex_file>
```

## Example

The following is an example of how to use the program. The regular expression is stored in
a file called `regex.txt`.

```bash
./regex2dfa regex.txt
```

The contents of `regex.txt` are:

```regex
a(b|c)*d
```
