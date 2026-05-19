#pragma once
#include <stdint.h>

class Mailbox {
public:
	static bool call(volatile uint32_t* buffer, uint32_t channel);
};