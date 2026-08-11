#include "com1.h"
#include "simple_print.h"
#include "string_helper.h"
#include <stdint.h>

void simple_printu(char *variable_name, uint64_t value)
{
	char buffer[64] = {0};
	uitoa(value, buffer);
	com1_write_c_MANGLED(variable_name);
	com1_write_c_MANGLED(" = ");
	com1_write_c_MANGLED(buffer);
	com1_write_c_MANGLED("\n");
}

void simple_printh(char *variable_name, uint64_t value)
{
	char buffer[64] = {0};
	uint_to_hex(value, buffer, true);
	com1_write_c_MANGLED(variable_name);
	com1_write_c_MANGLED(" = ");
	com1_write_c_MANGLED(buffer);
	com1_write_c_MANGLED("\n");
}
