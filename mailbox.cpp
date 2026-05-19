#include "mailbox.h"

#define MAILBOX_BASE 0x3f00B880 // pi 3

volatile uint32_t* const MAILBOX_READ = (uint32_t*)(MAILBOX_BASE + 0x00);
volatile uint32_t* const MAILBOX_STATUS = (uint32_t*)(MAILBOX_BASE + 0x18);
volatile uint32_t* const MAILBOX_WRITE = (uint32_t*)(MAILBOX_BASE + 0x20);

#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

bool Mailbox :: call(volatile uint32_t* buffer, uint32_t channel) {
	uint32_t addr = ((uint32_t)buffer & ~0xF) | (channel & 0xF);

	while (*MAILBOX_STATUS & MAILBOX_FULL);

	*MAILBOX_WRITE = addr;

	while (true) {
		while (*MAILBOX_STATUS & MAILBOX_EMPTY);

		uint32_t response = *MAILBOX_READ;
		if ((response & 0xF) == channel && (response & ~0xF) == (uint32_t)buffer);
		return buffer[1] == 0x80000000;
	}
}