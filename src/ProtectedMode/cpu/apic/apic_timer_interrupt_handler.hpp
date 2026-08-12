
#pragma once
#include "core_count.h"
#include "stdint.h"

extern "C"
{
	// C functions.
	// Put the interrupt handler that use extern C here (They will be used by assembly)

	void					 apic_wait_interrupt_handler(); // Could also just do it in raw assembly
	extern volatile bool	 apic_wait_interrupt_handled[MAX_CORE_COUNT];
	extern volatile uint32_t apic_wait_loop_count[MAX_CORE_COUNT];
}

namespace apic_timer
{
namespace handlers
{

constexpr uint8_t apic_wait_interrupt	   = 58; //
constexpr uint8_t apic_timer_fn1_interrupt = 59; // I'mma reserved these right now
constexpr uint8_t apic_timer_fn2_interrupt = 60; //

} // namespace handlers
} // namespace apic_timer
