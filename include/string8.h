#ifndef STRING8_H
#define STRING8_H

#include "arena.h"
#include "types.h"

#include <string.h>

typedef struct {
  char *data;
  u64 size;
} STRING8;

#ifdef STUFF_IMPLEMENTED
STRING8 string8_create(ARENA *arena, char *c_str) {
  STRING8 result = {0};
  result.size = strlen(c_str);
  result.data = arena_alloc(arena, result.size + 1);
  if (!result.data) {
    printf("arena_alloc failed at FILE: %s, LINE: %d\n", __FILE__, __LINE__);
    exit(1);
  }
  memcpy(result.data, c_str, result.size + 1);
  return result;
}
#endif

#endif // STRING8_H
