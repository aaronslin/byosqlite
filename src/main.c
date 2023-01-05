#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef enum {
  // Meta commands
  TOKEN_EXIT,
  TOKEN_TABLES,
  // Commands
  TOKEN_INSERT,
  TOKEN_SELECT,
  // Punctuation
  TOKEN_STRING
} TokenType;

typedef enum {
  STATUS_SUCCESS,
  STATUS_PARSE_FAILURE
} Status;

typedef struct {
  TokenType type;
  char* literal;
  int length;
} Token; 

typedef struct {
  size_t count;
  size_t capacity;
  Token* tokens;
} Statement;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  if (input_buffer) {
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
  } else {
    printf("[internal] Error: Failed to create an input buffer.\n");
    exit(EXIT_FAILURE);
  }
}

Statement* new_statement() {
  Statement* statement = malloc(sizeof(Statement));

  if (statement) {
    // (alin) perhaps managing arrays should be abstracted out. init, append, free
    statement->count = 0;
    statement->capacity = 1;
    statement->tokens = malloc(1 * sizeof(Token));
    return statement;
  } else {
    printf("[internal] Error: Failed to create statement.\n");
    exit(EXIT_FAILURE);
  }
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

void append_token(Statement* statement, Token* token) {
  if (statement->count == statement->capacity) {
    printf("reallocating.\n");
    statement->capacity *= 2;
    // check for NULL?
    statement->tokens = realloc(statement->tokens, (statement->capacity)*sizeof(Token));
  }
  statement->tokens[statement->count] = *token;
  statement->count += 1;
}

Status create_token(InputBuffer* input_buffer, Statement* statement, int start_index, int index) {
  if (start_index != index) {
    // (alin) why do I need to malloc here? why can't I just `Token* token;`?
    Token* token = malloc(sizeof(Token));
    token->length = index - start_index;
    token->literal = malloc((token->length) * sizeof(char));
    strncpy(token->literal, input_buffer->buffer + start_index, token->length);

    if (strcmp(token->literal, ".exit") == 0) {
      printf("exit");
      token->type = TOKEN_EXIT;
    } else if (strcmp(token->literal, ".tables") == 0) {
      printf("tables");
      token->type = TOKEN_TABLES;
    } else if (strcmp(token->literal, "insert") == 0) {
      printf("insert");
      token->type = TOKEN_INSERT;
    } else if (strcmp(token->literal, "select") == 0) {
      printf("select");
      token->type = TOKEN_SELECT;
    } else {
      // (alin) todo: catch this
      // Eventually this needs to be adapted to take table names, column names, etc.
      free(token);
      return STATUS_PARSE_FAILURE;
    }
    
    // How does printf know how many characters to print for token->literal? is token->length needed?
    printf("Creating token at %p (%s).\n", token, token->literal);
    append_token(statement, token);
  }
  return STATUS_SUCCESS;
}

void parse_command(InputBuffer* input_buffer, Statement* statement) {
  int index=0, start_index=0;

  while (index < input_buffer->input_length) {
    if (input_buffer->buffer[index] == ' ') {
      create_token(input_buffer, statement, start_index, index);
      index+=1;
      start_index=index;
    } else {
      index+=1;
    }
  }

  create_token(input_buffer, statement, start_index, index);
}

void execute_statement(Statement* statement) {
  printf("Executing a statement.\n");
  for (int i=0; i<statement->count; i=i+1) {
    Token token = statement->tokens[i];
    printf("Token* at %p is: %u.\n", &(statement->tokens[i]), token.type);
  }
}

int main(int argc, char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  printChunk(&chunk);

  writeChunk(&chunk, 'a');
  writeChunk(&chunk, 'o');
  printChunk(&chunk);

  writeChunk(&chunk, 'e');
  writeChunk(&chunk, 'u');
  printChunk(&chunk);

  writeChunk(&chunk, 'a');
  writeChunk(&chunk, 'o');
  writeChunk(&chunk, 'e');
  writeChunk(&chunk, 'u');
  writeChunk(&chunk, 'i');
  printChunk(&chunk);

  freeChunk(&chunk);
}
//int main(int argc, char* argv[]) {
//  InputBuffer* input_buffer = new_input_buffer();
//
//  while (true) {
//    print_prompt();
//    read_input(input_buffer);
//    Statement* statement = new_statement();
//    parse_command(input_buffer, statement);
//    execute_statement(statement);
//  }
//}

