#include "apic_timer_interrupt_handler.hpp"
#include "apic_timers.hpp"
#include "apic_wait.hpp"

// Wait and timer_interrupt_handler seems to be somewaht overlapping

volatile bool	  apic_wait_interrupt_handled[MAX_CORE_COUNT];
volatile uint32_t apic_wait_loop_count[MAX_CORE_COUNT];

using namespace apic;
using namespace apic_timer;

void start_timer_count(uint8_t vector, uint64_t count, enum timer_mode::type timer_mode, mask::type mask = mask::enable)
{
	constexpr uint64_t max_count = UINT32_MAX;

	constexpr divide_configuration::type configurations[] = {
		divide_configuration::divide_by_1,
		divide_configuration::divide_by_2,
		divide_configuration::divide_by_4,
		divide_configuration::divide_by_8,
		divide_configuration::divide_by_16,
		divide_configuration::divide_by_32,
		divide_configuration::divide_by_64,
		divide_configuration::divide_by_128,
	};

	for (auto configuration : configurations)
	{
		uint64_t divider = divide_configuration::to_value(configuration);

		uint64_t timer_count = count / divider;

		if (timer_count <= max_count)
		{
			apic_timer::start_timer(vector, static_cast<uint32_t>(timer_count), configuration, timer_mode, mask);

			return;
		}
	}

	abort_msg("Timer count is too large for the LAPIC timer\n");
}

void start_timer_seconds(uint8_t vector, double seconds, enum timer_mode::type timer_mode, mask::type mask = mask::enable)
{
	assert(apic_frequency != 0, "Apic frequency is 0, it wasn't synchronised. Can't call wait!\n");
	uint64_t count = static_cast<uint64_t>(seconds * apic_frequency);

	start_timer_count(vector, count, timer_mode, mask);
}

void start_timer_seconds_single_shot(uint8_t vector, double seconds)
{
	start_timer_seconds(vector, seconds, timer_mode::single_shot, mask::enable);
}

void start_timer_seconds_periodic(uint8_t vector, double seconds)
{
	start_timer_seconds(vector, seconds, timer_mode::repeat, mask::enable);
}

void start_timer_count_single_shot(uint8_t vector, uint64_t count)
{
	start_timer_count(vector, count, timer_mode::single_shot, mask::enable);
}

void start_timer_count_periodic(uint8_t vector, uint64_t count)
{
	start_timer_count(vector, count, timer_mode::repeat, mask::enable);
}

void apic_wait::quick_wait(uint32_t count)
{
	// assume implemented
	uint8_t core_id						 = apic::get_core_id_fast();
	apic_wait_interrupt_handled[core_id] = false;
	start_timer_count_single_shot(apic_timer::handlers::apic_wait_interrupt, count);
	while (!apic_wait_interrupt_handled[core_id])
	{
		// Wait and poll for it to be done
	}
}

void apic_wait::quick_wait_n_times(uint32_t count, uint32_t n)
{
	uint8_t core_id						 = apic::get_core_id_fast();
	apic_wait_interrupt_handled[core_id] = false;
	apic_wait_loop_count[core_id]		 = 0;
	start_timer_count_periodic(apic_timer::handlers::apic_wait_interrupt, count);

	while (apic_wait_loop_count[core_id] < n)
	{
		// Wait and poll for it to be done
	}
	stop_perioic_timer();
}

void apic_wait::wait_c(uint64_t count)
{
	constexpr uint64_t max_count = UINT32_MAX;

	uint64_t number_of_full_waits = count / max_count;
	uint32_t leftover_count		  = count % max_count;

	constexpr bool fast = false;
	if (fast)
	{

		quick_wait_n_times(max_count, number_of_full_waits);
	}
	else
	{

		for (uint64_t i = 0; i < number_of_full_waits; ++i)
		{
			quick_wait(max_count);
		}
	}

	if (leftover_count > 0)
	{
		quick_wait(leftover_count);
	}
}

void apic_wait::wait(double seconds)
{
	assert(apic_frequency != 0, "Apic frequency is 0, it wasn't synchronised. Can't call wait!\n");
	uint64_t count = static_cast<uint64_t>(seconds * apic_frequency);
	// It doesn't quit work with an exact time.
	// It seem to be off

	wait_c(count);
}
