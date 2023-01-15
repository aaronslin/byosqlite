#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->token = NULL;
}

void writeChunk(Chunk* chunk, Token token) {
  if (chunk->count + 1 > chunk->capacity) {
    // (alin) is this supposed to be an int
    int newCapacity = GROW_CAPACITY(chunk->capacity);
    chunk->token = GROW_ARRAY(Token, chunk->token, chunk->capacity, newCapacity);
    chunk->capacity = newCapacity;
  }
  
  chunk->token[chunk->count] = token;
  chunk->count += 1;
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(Token, chunk->token, chunk->capacity);
  initChunk(chunk);
}

void printChunk(Chunk* chunk) {
  printf("Printing chunk at %p. ( %zu / %zu )\n", chunk, chunk->count, chunk->capacity);
  for(int i=0; i<chunk->count; i=i+1) {
    printf(": type (%d), start(%c), length (%d) \n", chunk->token[i].type, chunk->token[i].start[0], chunk->token[i].length);
  }
}

void initInputBuffer(InputBuffer* inputBuffer) {
  inputBuffer->count = 0;
  inputBuffer->capacity = 0;
  inputBuffer->buffer = NULL;
}

void freeInputBuffer(InputBuffer* inputBuffer){
  free(inputBuffer->buffer);
  initInputBuffer(inputBuffer);
}

void readInputBuffer(InputBuffer* inputBuffer) {
  size_t bytesRead = getline(&(inputBuffer->buffer), &(inputBuffer->capacity), stdin);

  if (bytesRead <= 0) {
    printf("[internal] Error: Failed to read any bytes.\n");
    exit(EXIT_FAILURE);
  }

  // Ignore the trailing newline.
  inputBuffer->count = bytesRead - 1;
  inputBuffer->buffer[bytesRead - 1] = 0;
}
