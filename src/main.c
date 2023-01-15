#include "common.h"
#include "chunk.h"
#include "scanner.h"

void print_prompt() {
  printf("db > ");
}

int main(int argc, char* argv[]) {
  InputBuffer inputBuffer;
  initInputBuffer(&inputBuffer);

  while (true) {
    print_prompt();
    readInputBuffer(&inputBuffer);

    Scanner scanner;
    Chunk chunk;
    initScanner(&scanner, &inputBuffer);
    initChunk(&chunk);

    runScanner(&scanner, &chunk);
    printChunk(&chunk);
  }
}
