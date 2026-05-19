#include "timer.h"

#define MMIO_BASE 0x3F000000

volatile uint32_t* TIMER_CLO =
	(volatile uint32_t*)(MMIO_BASE + 0x3004);

uint32_t timer_get_ticks()
{
	return *TIMER_CLO;
}

void delay_ms(uint32_t ms)
{
	uint32_t start = timer_get_ticks();

	while ((timer_get_ticks() - start) < (ms * 1000))
	{
	}
}