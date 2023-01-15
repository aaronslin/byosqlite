#ifndef byosqlite_scanner_h
#define byosqlite_scanner_h

#include "common.h"
#include "chunk.h"

typedef struct {
  char* start;
  char* current;
  // (alin) this can be simplified from an InputBuffer to a char* array.
  InputBuffer* inputBuffer;
} Scanner;

void initScanner(Scanner* scanner, InputBuffer* inputBuffer);
Status runScanner(Scanner* scanner, Chunk* chunk);

#endif
