#include "com1.h"
#include "framebuffer_shared.h"
#include "simple_print.h"
#include "string_helper.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

__attribute__((noinline)) void fill_screen(volatile uint32_t color)
{

	volatile uint32_t *fb_ptr = (volatile uint32_t *)FB_MMIO_BASE;
	volatile uint32_t *fb_end = fb_ptr + 1920 * 1080;
	for (volatile uint32_t *mmio_ptr = fb_ptr; mmio_ptr < fb_end; mmio_ptr++)
	{
		*mmio_ptr = color;
	}
}

void kernel64_zig_main();

extern uint64_t __debug_info_start;
void			kernel64_main()
{
	com1_init();

	const char x[] = "\n\n=============Hello from 64 bit================\n\n";
	com1_write_c_MANGLED(x);
	com1_write_c_MANGLED("Com1 write ro data\n");

	uint32_t *unit_length_location = (uint32_t *)&__debug_info_start;
	uint32_t  unit_length		   = *unit_length_location;
	simple_printh("address", (uint64_t)unit_length_location);
	simple_printu("unit length", unit_length);

	// fill_screen(0x000000);

	com1_write_c_MANGLED("Going to Zig! No More C\n");

	kernel64_zig_main();
}
