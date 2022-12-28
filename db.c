#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  if (input_buffer) {
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
  }
  return NULL;
}

void print_prompt() {
  printf("db > ");
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("[internal] Error: Failed to read any bytes.\n");
    exit(EXIT_FAILURE);
  }

  // Ignore the trailing newline.
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
  input_buffer = NULL;
}

int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  if (input_buffer == NULL) {
    printf("[internal] Error: Failed to create an input buffer.\n");
    exit(EXIT_FAILURE);
  }

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Command not recognized: '%s'.\n", input_buffer->buffer);
    }
  }
}


/*

Task:
 Write a REPL that exits on `.exit` and throws "unrecognized command" on everything else.

Notes:
 - malloc
 - sizeof
 - typedef
 - struct
 - a->b
 - free

Notes (part 2):
 - `getline` allocates ceil(|bytes_read|) memory for the buffer, and tells you what it allocated in `buffer_length`.
   If the input commands are ["hi", "aoeuasdf", "hi"], and you try to access `input_buffer->buffer[bytes_read + k]`,
     - for k=0, this succeeds on all inputs because of the null terminator
     - for k=1, this runs but is undefined behavior on the 1st and 2nd inputs, and leads to a segfault on the 3rd.
*/
