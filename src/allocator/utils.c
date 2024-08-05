#include <xll/allocator/utils.h>

inline size_t xll_page_align(size_t size) {
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    return (size + page_size - 1) & ~(page_size - 1);
}
