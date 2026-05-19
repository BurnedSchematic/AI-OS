#include "gpu_memory.h"
#include "mailbox.h"

static volatile uint32_t mailbox[36]
__attribute__((aligned(16)));

bool gpu_malloc(GPUMemory* mem,
    uint32_t size,
    uint32_t alignment,
    uint32_t flags)
{
    // -------------------------------------------------
    // Allocate GPU memory
    // -------------------------------------------------

    mailbox[0] = 9 * 4 + 8;
    mailbox[1] = 0x00000000;

    mailbox[2] = 0x0003000C;
    mailbox[3] = 12;
    mailbox[4] = 0;

    mailbox[5] = size;
    mailbox[6] = alignment;
    mailbox[7] = flags;

    mailbox[8] = 0;

    if (!Mailbox::call((uint32_t*)mailbox, 8))
    {
        return false;
    }

    mem->handle = mailbox[5];

    if (!mem->handle)
    {
        return false;
    }

    // -------------------------------------------------
    // Lock GPU memory
    // -------------------------------------------------

    mailbox[0] = 7 * 4 + 8;
    mailbox[1] = 0x00000000;

    mailbox[2] = 0x0003000D;
    mailbox[3] = 4;
    mailbox[4] = 0;

    mailbox[5] = mem->handle;

    mailbox[6] = 0;

    if (!Mailbox::call((uint32_t*)mailbox, 8))
    {
        return false;
    }

    mem->bus_address = mailbox[5];

    if (!mem->bus_address)
    {
        return false;
    }

    mem->arm_address =
        mem->bus_address & 0x3FFFFFFF;

    return true;
}

bool gpu_free(GPUMemory* mem)
{
    //Unlock memory

    mailbox[0] = 7 * 4 + 8;
    mailbox[1] = 0;

    mailbox[2] = 0x0003000E;
    mailbox[3] = 4;
    mailbox[4] = 0;

    mailbox[5] = mem->handle;

    mailbox[6] = 0;

    if (!Mailbox::call((uint32_t*)mailbox, 8))
    {
        return false;
    }

    //Release Memory

    mailbox[0] = 7 * 4 + 8;
    mailbox[1] = 0;

    mailbox[2] = 0x0003000F;
    mailbox[3] = 4;
    mailbox[4] = 0;

    mailbox[5] = mem->handle;

    mailbox[6] = 0;

    if (!Mailbox::call((uint32_t*)mailbox, 8))
    {
        return false;
    }

    return true;
}