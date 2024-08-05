#include <stdio.h>

#include "xll/allocator/arena_allocator.h"

int main(void) {
    XllArenaAllocator *allocator = xll_arena_init(409599999);
    size_t n = 10;
    float **arr = (float **)xll_arena_calloc(allocator, n, sizeof(float *));
    for (size_t i = 0; i < n; ++i) {
        float *a = xll_arena_malloc(allocator, sizeof(float));
        printf("Float Pointer: %p\n", (void *)a);
        *a = (float)(i + 2);
        arr[i] = a;
    }

    for (size_t i = 0; i < n; ++i) {
        float *a = arr[i];
        printf("Value: %f\n", *a);
    }

    int code = xll_arena_free(&allocator);
    printf("Code: %i\n", code);
    printf("Allocator Pointer: %s\n", ((allocator == 0) ? "NOT NULL" : "NULL"));
    return 0;
}
