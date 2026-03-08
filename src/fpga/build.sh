#!/usr/bin/env bash

# build.sh - compile and simulate 1-bit adder

# Name of the output simulation executable
SIM="sim_adder1bit"

# Verilog source files
SRC=("adder1bit.v" "testbench.v")

# Compile the Verilog code
iverilog "adder1bit.v" "testbench.v" -o "sim_adder1bit"
if [ $? -ne 0 ]; then
	echo "Compilation failed!"
	exit 1
fi
echo "Compilation successful: $SIM created."

# Run the simulation
vvp "$SIM"
if [ $? -ne 0 ]; then
	echo "Simulation failed!"
	exit 2
fi
echo "Simulation completed."

# Open the waveform in GTKWave
if [ -f "adder1bit.vcd" ]; then
	gtkwave adder1bit.vcd &
else
	echo 'VCD file not found. Did your testbench include $dumpfile and $dumpvars?'
fi
