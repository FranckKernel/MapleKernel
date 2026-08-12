#include "apic.hpp"
#include "apic_timer_interrupt_handler.hpp"
#include "apic_timers.hpp"
#include "apic_wait.hpp"

// Wait and timer_interrupt_handler seems to be somewaht overlapping

extern "C" void apic_wait_interrupt_handler()
{
}

namespace apic_timer
{

namespace handlers
{

}

} // namespace apic_timer
