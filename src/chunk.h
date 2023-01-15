#ifndef byosqlite_chunk_h
#define byosqlite_chunk_h

#include "common.h"

typedef enum {
  OP_CONSTANT
} OpCode;

// A buffer for reading SQL inputs to the interpreter.
typedef struct {
  size_t count;
  size_t capacity;
  char* buffer;
} InputBuffer;

typedef enum {
  // Meta commands
  TOKEN_EXIT,
  TOKEN_TABLES,
  // Keywords
  TOKEN_INSERT,
  TOKEN_INTO,
  TOKEN_SELECT,
  TOKEN_VALUES,
  // Punctuation
  TOKEN_COMMA,
  TOKEN_IDENTIFIER,
  TOKEN_PAREN_OPEN,
  TOKEN_PAREN_CLOSE,
  // EOF
  TOKEN_EOF
} TokenType;

// Represents a token such as "SELECT" or "("
typedef struct {
  TokenType type;
  char* start;
  int length;
} Token; 

typedef struct {
  size_t count;
  size_t capacity;
  // (alin) For performance, a chunk should really be storing a sequence of
  // opcodes and values. I don't understand SQL grammar well enough to
  // design this.
  Token* token;
} Chunk;

// Chunk API
void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, Token token);
void freeChunk(Chunk* chunk);
void printChunk(Chunk* chunk);

// InputBuffer API
void initInputBuffer(InputBuffer* inputBuffer);
void freeInputBuffer(InputBuffer* inputBuffer);
void readInputBuffer(InputBuffer* inputBuffer);

#endif
