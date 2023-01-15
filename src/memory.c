#include "memory.h"

void* reallocate(void* ptr, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(ptr);
    return NULL;
  }
  
  void* newPtr = realloc(ptr, newSize);
  if (!newPtr) {
    printf("Failed to resize array. Exiting.\n");
    exit(1);
  }
  return newPtr;
}
