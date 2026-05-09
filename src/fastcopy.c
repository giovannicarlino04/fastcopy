/*
  TODO's:
  - Show progress bar during copy
  - Support recursive directory copying
  - Use platform-specific I/O intrinsics
*/

#define STUFF_IMPLEMENTED
#include "arena.h"
#include "file8.h"
#include "string8.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s <source file> <dest file>\n", argv[0]);
    exit(1);
  }

  ARENA arena = arena_create(4096);
  STRING8 source_path = string8_create(&arena, argv[1]);
  STRING8 dest_path = string8_create(&arena, argv[2]);

  if (!file_copy(&arena, &source_path, &dest_path)) {
    printf("fastcopy failed\n");
    exit(1);
  }

  arena_destroy(&arena);
}
