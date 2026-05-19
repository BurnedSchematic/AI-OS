#pragma once

#include <stdint.h>

struct GPUMemory
{
    uint32_t handle;
    uint32_t bus_address;
    uint32_t arm_address;
};

bool gpu_malloc(GPUMemory* mem,
    uint32_t size,
    uint32_t alignment,
    uint32_t flags);

bool gpu_free(GPUMemory* mem);