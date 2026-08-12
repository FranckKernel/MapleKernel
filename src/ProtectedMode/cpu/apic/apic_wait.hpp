#pragma once
#include "core_count.h"
#include <stdint.h>

namespace apic_wait
{

void wait_c(uint64_t count);
void wait(double seconds);

// Optional : The quick wait functions
void quick_wait(uint32_t count);
void quick_wait_n_times(uint32_t count, uint32_t n);
} // namespace apic_wait
