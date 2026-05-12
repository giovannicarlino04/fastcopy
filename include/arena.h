#ifndef ARENA_H
#define ARENA_H

#include "types.h"
#include "log.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ARENA_ALIGNMENT _Alignof(max_align_t)

typedef struct ARENA_BLOCK {
    struct ARENA_BLOCK *next;
    u64 capacity;
    u64 offset;
} ARENA_BLOCK;

#define ARENA_HEADER_SIZE                                                      \
((sizeof(ARENA_BLOCK) + ARENA_ALIGNMENT - 1) & ~(ARENA_ALIGNMENT - 1))

typedef struct {
    ARENA_BLOCK *first;
    ARENA_BLOCK *current;
    u64 block_size;
} ARENA;

typedef struct {
    ARENA_BLOCK *block;
    u64 offset;
} ARENA_SAVE;

#ifdef STUFF_IMPLEMENTED

ARENA arena_create(u64 block_size) {
    ARENA arena = {0};
    arena.block_size = block_size ? block_size : 4096;
    return arena;
}

static ARENA_BLOCK *arena_new_block(ARENA *arena, u64 min_capacity) {
    u64 capacity =
        arena->block_size < min_capacity ? min_capacity : arena->block_size;
    ARENA_BLOCK *block = (ARENA_BLOCK *)malloc(ARENA_HEADER_SIZE + capacity);
    if (!block) {
        log(ERROR, "malloc failed");
        exit(1);
    }
    block->next = NULL;
    block->capacity = capacity;
    block->offset = 0;
    return block;
}

void *arena_alloc(ARENA *arena, u64 size) {
    if (size == 0)
        size = 1;
    if (!arena->current) {
        arena->current = arena_new_block(arena, size);
        arena->first = arena->current;
    }
    ARENA_BLOCK *block = arena->current;
    u64 aligned_offset =
    (block->offset + ARENA_ALIGNMENT - 1) & ~(ARENA_ALIGNMENT - 1);
    if (aligned_offset + size > block->capacity) {
        arena->block_size *= 2;
        ARENA_BLOCK *new_block = arena_new_block(arena, size);
        arena->current->next = new_block;
        arena->current = new_block;
        block = new_block;
        aligned_offset = 0;
    }
    block->offset = aligned_offset + size;
    return (char *)block + ARENA_HEADER_SIZE + aligned_offset;
}

void arena_destroy(ARENA *arena) {
    ARENA_BLOCK *block = arena->first;
    while (block) {
        ARENA_BLOCK *next = block->next;
        free(block);
        block = next;
    }
    arena->first = NULL;
    arena->current = NULL;
}

void arena_reset(ARENA *arena) {
    ARENA_BLOCK *block = arena->first;
    while (block) {
        block->offset = 0;
        block = block->next;
    }
    arena->current = arena->first;
}

ARENA_SAVE arena_save(ARENA *arena) {
    ARENA_SAVE save = {0};
    if (arena->current) {
        save.block = arena->current;
        save.offset = arena->current->offset;
    }
    return save;
}

void arena_restore(ARENA *arena, ARENA_SAVE save) {
    if (save.block) {
        ARENA_BLOCK *block = save.block->next;
        while (block) {
            ARENA_BLOCK *next = block->next;
            free(block);
            block = next;
        }
        save.block->next = NULL;
        save.block->offset = save.offset;
        arena->current = save.block;
    }
}

#endif

#endif // ARENA_H
