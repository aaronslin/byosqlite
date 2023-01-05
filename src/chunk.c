#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
}

void writeChunk(Chunk* chunk, char code) {
  if (chunk->count + 1 > chunk->capacity) {
    // (alin) is this supposed to be an int
    int newCapacity = GROW_CAPACITY(chunk->capacity);
    chunk->code = GROW_ARRAY(char, chunk->code, chunk->capacity, newCapacity);
    chunk->capacity = newCapacity;
  }
  
  // (alin) it surprises me this is valid, given that code is a char*, not char[]
  chunk->code[chunk->count] = code;
  chunk->count += 1;
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(Chunk, chunk->code, chunk->capacity);
  initChunk(chunk);
}

void printChunk(Chunk* chunk) {
  printf("Printing chunk at %p. ( %zu / %zu )\n", chunk, chunk->count, chunk->capacity);
  for(int i=0; i<chunk->count; i=i+1) {
    printf(": %c\n", chunk->code[i]);
  }
}
