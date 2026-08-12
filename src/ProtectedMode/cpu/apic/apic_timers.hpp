#pragma once
#include "stdint.h"

#include "apic.hpp"
#include "apic_io.hpp"

#include "multicore.h"

// Temporary apic internal include
#include "apic_internals.hpp"

namespace apic_timer
{

extern uint64_t	  apic_frequency;
constexpr uint8_t apic_sync_interrupt = 61; //

void start_timer(uint8_t vector, uint32_t initial_count, enum apic::divide_configuration::type divide_configuration,
	enum apic::timer_mode::type timer_mode, apic::mask::type mask);

void stop_perioic_timer();
void mask_timer();
void unmask_timer();

uint32_t sync_apic_with_pit();
} // namespace apic_timer
