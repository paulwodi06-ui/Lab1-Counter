#include "verilated.h" // Provides the main Verilator simulation functionality
#include "verilated_vcd_c.h" // Allows us to record signal waveforms in a .vcd file, which GTKWave can display
#include "Vcounter.h" // Provides access to the C++ model of my SystemVerilog counter module. Verilator generates this header when I compile the design
#include "vbuddy.cpp" // makes the Vbuddy functions available to my testbench
#include <unistd.h> // gives us access to usleep(), which pauses execution for a specified number of microseconds

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vcounter* top = new Vcounter; // creates an instance of the counter hardware model

    if (vbdOpen() != 1) {
    return 1;
    }

    vbdHeader("Lab 1: Counter");

    Verilated::traceEverOn(true); 

    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("Vcounter.vcd");

    top->clk = 0;
    top->rst = 1;
    top->en = 0;

    int sim_time = 0;

    while (sim_time < 200) {

    if (sim_time == 4) {
    top->rst = 0;
    }

    // Read the button-controlled flag from Vbuddy
    top->en = vbdFlag();

    top->clk = !top->clk;
    top->eval(); // tells Verilator to evaluate the hardware design using its current input signals
    vbdHex(4, (int(top->count) >> 16) & 0xF);
    vbdHex(3, (int(top->count) >> 8) & 0xF);
    vbdHex(2, (int(top->count) >> 4) & 0xF);
    vbdHex(1, int(top->count) & 0xF);

    vbdCycle(sim_time / 2);
    usleep(100000);
    tfp->dump(sim_time);

    sim_time++;
    }

    vbdClose();

    tfp->close();
    delete tfp;
    delete top;

    return 0;
}



