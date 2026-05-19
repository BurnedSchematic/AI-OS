#include "memory.h"

static uint32_t heap_ptr = 0x01000000;

void* alloc_aligned(uint32_t size,
    uint32_t alignment)
{
    heap_ptr =
        (heap_ptr + alignment - 1)
        & ~(alignment - 1);

    void* result = (void*)heap_ptr;

    heap_ptr += size;

    return result;
}
