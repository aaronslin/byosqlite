#ifndef byosqlite_common_h
#define byosqlite_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  STATUS_SUCCESS,
  STATUS_SCAN_SUCCESS,
  STATUS_SCAN_UNRECOGNIZED_CHARACTER
} Status;

#endif
