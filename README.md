# Overview

This is a follow-along of `cstack`'s "Build your own SQLite" tutorial [here](https://cstack.github.io/db_tutorial/). 

Files named `part{n}.c` are the code snippets found at the end of each section. To view diffs:

```
# In vim, with `part{n+1}.c` open:
:vert diffsplit part{n}.c

# In the terminal
vimdiff part{n}.c part{n+1}.c

```


# Notes


## Ch. 1
 Write a REPL that exits on `.exit` and throws "unrecognized command" on everything else.

Notes:
 - malloc
 - sizeof
 - typedef
 - struct
 - a->b
 - free

## Ch. 2

 - `getline` allocates ceil(|bytes_read|) memory for the buffer, and tells you what it allocated in `buffer_length`.
   If the input commands are ["hi", "aoeuasdf", "hi"], and you try to access `input_buffer->buffer[bytes_read + k]`,
     - for k=0, this succeeds on all inputs because of the null terminator
     - for k=1, this runs but is undefined behavior on the 1st and 2nd inputs, and leads to a segfault on the 3rd.

## Crafting Interpreters Ch. 14-16

 - Memory efficiency and performance are two huge goals. In `jlox` one of the core objects was the `Expr`
   AST, but this is memory inefficient and would require too many lookups to recurse through. Instead,
   `clox` has a couple of innovations:
    - Each operation is an 8-bit code, instead of a new object. If the operation has associated
      "metadata", the value (or a pointer to it) comes after the value. For example, a chunk representing 
      `1 + 2` might look like: `[OP_CONST] [1] [OP_PLUS] [OP_CONST] [2]`.

    - Interpreting without recursion: It is harder for `clox` to recurse through an AST because the
      instructions are provided linearly as a stream of operations. Surprisingly, the VM interpreter 
      can compute with a single forward pass using *only a stack* to track computation state.
      
      For example: `(1+2)*3` could be represented by the following operations:
      ```
      push(1)
      push(2)
      push(add(pop(), pop()))
      push(mul(pop(), pop()))
      ```

      This is surprising and not-so-obvious!
    - Scanning is similar to the approach for `jlox`. It is characterized by mostly single-lookahead
      scanning (e.g. to disambiguuate `=[space]` and `==`, and occasionally double-lookahead
      (e.g. to identify `//`). The main differences are:
      - Instead of storing the lexemes by value, we store pointers to the start and ends of them.
      - Instead of storing keywords in a hashmap, we use a DFA to disambuguate them.

## Ch. 3: Insert and print tables

 - See [this](https://github.com/AlecStrong/sqlite-bnf/blob/master/sqlite.bnf) for a BNF of SQLite syntax.
