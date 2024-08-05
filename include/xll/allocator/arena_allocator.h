#ifndef LEAKLESS_ARENA_ALLOCATOR
#define LEAKLESS_ARENA_ALLOCATOR

#include <stddef.h>

typedef struct {
    size_t size;
    size_t offset;
} XllArenaAllocator;

XllArenaAllocator *xll_arena_init(size_t arena_size);

void *xll_arena_malloc(XllArenaAllocator *allocator, size_t size);
void *xll_arena_calloc(XllArenaAllocator *allocator, size_t num, size_t size);
int xll_arena_free(XllArenaAllocator **allocator);

#endif  // LEAKLESS_ARENA_ALLOCATOR
