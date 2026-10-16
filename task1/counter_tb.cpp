#include "verilated.h" // Provides the main Verilator simulation functionality
#include "verilated_vcd_c.h" // Allows us to record signal waveforms in a .vcd file, which GTKWave can display
#include "Vcounter.h" // Provides access to the C++ model of my SystemVerilog counter module. Verilator generates this header when I compile the design

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vcounter* top = new Vcounter; // creates an instance of the counter hardware model

    Verilated::traceEverOn(true); 

    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("Vcounter.vcd");

    top->clk = 0;
    top->rst = 1;
    top->en = 0;

    int sim_time = 0;

    while (sim_time < 40) {

    if (sim_time == 4) {
        top->rst = 0;
        top->en = 1;
    }

    if (sim_time == 20) {
        top->en = 0;
    }

    if (sim_time == 28) {
        top->en = 1;
    }

    top->clk = !top->clk;
    top->eval(); // tells Verilator to evaluate the hardware design using its current input signals
    tfp->dump(sim_time);

    sim_time++;
    }

    tfp->close();
    delete tfp;
    delete top;

    return 0;
}



