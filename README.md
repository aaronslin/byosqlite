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
