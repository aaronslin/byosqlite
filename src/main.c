#include "common.h"
#include "chunk.h"
#include "scanner.h"
#include "table.h"

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

    // table tests
    Table table;
    initTable(&table);

    Row row;
    strcpy(row.username, "dragon96");
    strcpy(row.email, "lin.aaron1@gmail.com");
    printTable(&table);
    insertRow(&table, &row);
    printTable(&table);

  }
}
