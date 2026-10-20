module counter #(
    parameter WIDTH = 8
)(
    input  logic             clk,
    input  logic             rst,
    input  logic             en,
    output logic [WIDTH-1:0] count
);
always_ff @(posedge clk)
    if (rst)
        count <= {WIDTH{1'b0}}; // 1'b0 represents a single binary zero
    else if (en)
        count <= count + 1'b1; // This adds 1 to the current value

endmodule
