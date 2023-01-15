#ifndef byosqlite_table_h
#define byosqlite_table_h

#include "common.h"

#define MAX_TABLE_NAME_LENGTH 80
#define MAX_ROW_STRING_LENGTH 80

// (alin) this is a fixed schema. This should change later
typedef struct {
  uint32_t id; // assumed to be auto-assigned as the PK
  char username[MAX_ROW_STRING_LENGTH];
  char email[MAX_ROW_STRING_LENGTH];
} Row;

typedef struct {
  char name[MAX_TABLE_NAME_LENGTH];
  int rowCount;
  int rowCapacity;
  Row* row;
  // (alin) to be factored out into a schema object once we have keys
  int nextId;
} Table;

void initTable(Table* table);
void printTable(Table* table);

Status insertRow(Table* table, Row* row);

#endif
