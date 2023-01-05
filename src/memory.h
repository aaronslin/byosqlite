#include "common.h"

#define GROW_CAPACITY(capacity) \
  (capacity < 8 ? 8 : 2 * capacity)

// (alin) if I defined this as a regular function, what is the type of `type`?
#define GROW_ARRAY(type, ptr, oldSize, newSize) \
  (type*) reallocate(ptr, sizeof(type) * oldSize, sizeof(type) * newSize)

#define FREE_ARRAY(type, ptr, oldSize) \
  reallocate(ptr, sizeof(type) * oldSize, 0)

void* reallocate(void* ptr, size_t oldSize, size_t newSize);
