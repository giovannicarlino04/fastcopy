#ifndef FILE_H
#define FILE_H
#include "arena.h"
#include "string8.h"

#include <stdio.h>

typedef struct {
  char *data;
  u64 size;
} FILE8;

#ifdef STUFF_IMPLEMENTED

FILE8 file_open(ARENA *arena, STRING8 *file_path) {
  FILE8 file = {0};
  FILE *c_file;
  fopen_s(&c_file, file_path->data, "rb");
  if (c_file == NULL) {
    printf("fopen failed at FILE: %s, LINE: %d\n", __FILE__, __LINE__);
    exit(1);
  }
  fseek(c_file, 0, SEEK_END);
  long s = ftell(c_file);
  if (s < 0) {
    printf("ftell failed at FILE: %s, LINE: %d\n", __FILE__, __LINE__);
    exit(1);
  }
  file.size = s;
  fseek(c_file, 0, SEEK_SET);
  file.data = arena_alloc(arena, file.size ? file.size : 1);
  if (!file.data) {
    printf("arena_alloc failed at FILE: %s, LINE: %d", __FILE__, __LINE__);
    exit(1);
  }
  fread(file.data, file.size, 1, c_file);
  fclose(c_file);
  return file;
}

b8 file_copy_to_file(FILE8 *source, FILE8 *dest) {
  if (!source || !source->data) {
    printf("ERROR: source file does not exist\n");
    exit(1);
  }
  FILE *check;
  FILE *c_dest;

  fopen_s(&check, dest->data, "rb");
  if (check) {
    fclose(check);
    printf("ERROR: destination file already exists\n");
    exit(1);
  }

  fopen_s(&c_dest, dest->data, "wb");
  if (!c_dest) {
    printf("fopen failed at FILE: %s, LINE: %d\n", __FILE__, __LINE__);
    exit(1);
  }
  fwrite(source->data, source->size, 1, c_dest);
  fclose(c_dest);
  return 1;
}

b8 file_copy(ARENA *arena, STRING8 *source_path, STRING8 *dest_path) {
  ARENA_SAVE save = arena_save(arena);
  FILE8 source = file_open(arena, source_path);
  FILE8 dest = {0};
  dest.data = dest_path->data;
  b8 result = file_copy_to_file(&source, &dest);
  arena_restore(arena, save);
  return result;
}
#endif

#endif // FILE_H
