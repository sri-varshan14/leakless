#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <xll/allocator/arena_allocator.h>
#include <xll/allocator/utils.h>

XllArenaAllocator *xll_arena_init(size_t arena_size) {
    size_t page_aligned_size =
        xll_page_align(arena_size + sizeof(XllArenaAllocator));
    void *allocator = mmap(NULL, page_aligned_size, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (allocator == MAP_FAILED) return NULL;
    XllArenaAllocator *allocator_ptr = allocator;
    allocator_ptr->size = arena_size;
    allocator_ptr->offset = 0;
    return allocator;
}

void *xll_arena_malloc(XllArenaAllocator *allocator, size_t size) {
    size_t cur_size = allocator->offset;
    if (cur_size + size > allocator->size - sizeof(XllArenaAllocator))
        return NULL;
    allocator->offset += size;
    printf("Allocating Size: %zu\n", size);
    return ((char *)allocator + sizeof(XllArenaAllocator) + cur_size);
}

void *xll_arena_calloc(XllArenaAllocator *allocator, size_t num, size_t size) {
    return xll_arena_malloc(allocator, size * num);
}

int xll_arena_free(XllArenaAllocator **allocator) {
    if (*allocator == NULL) return -1;
    XllArenaAllocator *allocator_internal = *allocator;
    size_t allocator_size =
        xll_page_align(sizeof(XllArenaAllocator) + allocator_internal->size);
    if (munmap(allocator_internal, allocator_size) != 0) return -2;
    allocator = NULL;
    return 0;
}
