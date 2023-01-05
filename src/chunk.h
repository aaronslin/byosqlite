#include "common.h"

typedef enum {
  OP_CONSTANT
} OpCode;

typedef struct {
  size_t count;
  size_t capacity;
  // (alin) temporary. this should be a uint8_t, but I'm not sure why it's not OpCode*
  char* code;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, char code);
void freeChunk(Chunk* chunk);
void printChunk(Chunk* chunk);
