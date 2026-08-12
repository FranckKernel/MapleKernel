#pragma once
#include "stdint.h"

#include "apic.hpp"
#include "apic_io.hpp"

#include "multicore.h"

// Temporary apic internal include
#include "apic_internals.hpp"

namespace apic_timer
{

constexpr uint8_t apic_sync_interrupt = 61; //
constexpr uint8_t apic_wait_interrupt = 62; // I have not verified if 62 is used somewhere

void start_timer(uint8_t vector, uint32_t initial_count, enum apic::divide_configuration::type divide_configuration,
	enum apic::timer_mode::type timer_mode, apic::mask::type mask);

void wait(double seconds);

uint32_t sync_apic_with_pit();
} // namespace apic_timer

extern "C" volatile bool	 apic_wait_isr_done[MAX_CORE_COUNT];
extern "C" volatile uint32_t apic_wait_loop_max[MAX_CORE_COUNT]; // Might be useless
extern "C" volatile uint32_t apic_wait_loop_count[MAX_CORE_COUNT];
