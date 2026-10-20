
#!/bin/sh

# Stop the script if a command fails
set -e

# Cleanup previous simulation files
rm -rf obj_dir
rm -f Vcounter.vcd

# Convert SystemVerilog into C++
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

# Compile the generated C++ code
make -j -C obj_dir/ -f Vcounter.mk Vcounter

# Run the executable simulation
obj_dir/Vcounter
