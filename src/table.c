#include "table.h"
#include "memory.h"

void initTable(Table* table) {
  // table->name = {};
  table->rowCount = 0;
  table->rowCapacity = 0;
  table->row = NULL;
  table->nextId = 1;
}

Status insertRow(Table* table, Row* row) {
  // Validate.
  //  - check if id is unique
  //  - check if an acceptable value is supplied, or if there is a default
  //  - check if the FK maps to an existing row

  // Assign a PK id automatically.
  row->id = table->nextId;
  table->nextId++;
  
  // Insert.
  if (table->rowCount + 1 > table->rowCapacity) {
    int newCapacity = GROW_CAPACITY(table->rowCapacity);
    table->row = GROW_ARRAY(Row, table->row, table->rowCapacity, newCapacity);
    table->rowCapacity = newCapacity;
  }
  
  table->row[table->rowCount] = *row;
  table->rowCount += 1;

  return STATUS_DML_OK;
}

// (alin) this implementation is very specific to the fixed schema
void printTable(Table* table) {
  int columnLen[2] = {5, 20};
  char buffer[columnLen[1]];

  // Print top edge
  printf("+");
  for (int i=0; i<sizeof(columnLen) / sizeof(int); i++) {
    if (i!=0) printf("+");
    for (int j=0; j<columnLen[i] + 2; j++) { printf("%c", '-'); }
  }
  printf("+\n");

  // Print rows
  for (int i=0; i<table->rowCount; i++) {
    Row row = table->row[i];
    printf("| %-5d | %-20s |\n", row.id, memcpy(buffer, row.username, columnLen[1]));
  }

  // Print bottom edge
  printf("+");
  for (int i=0; i<sizeof(columnLen) / sizeof(int); i++) {
    if (i!=0) printf("+");
    for (int j=0; j<columnLen[i] + 2; j++) { printf("%c", '-'); }
  }
  printf("+\n");
}
