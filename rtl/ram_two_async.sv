// -----------------------------------------------------------------------------
// File Name: ram_two_async.sv
// Description:
//     An asynchronous two-port RAM module where the write and read ports
//     operate on independent clocks. This module supports simultaneous write
//     and read operations across different clock domains.
//
// Author: shsjung (github.com/shsjung)
// Date Created: 2024-12-12
// -----------------------------------------------------------------------------

`define SIM_LOG

module ram_two_async #(
    parameter  int Width = 32,
    parameter  int Depth = 256,
    localparam int Aw    = $clog2(Depth)
) (
    input              wclk_i,
    input              we_i,
    input  [   Aw-1:0] waddr_i,
    input  [Width-1:0] wdata_i,

    input              rclk_i,
    input              re_i,
    input  [   Aw-1:0] raddr_i,
    output [Width-1:0] rdata_o
);

    logic [Width-1:0] memory[Depth];
    logic [Width-1:0] rdata;

    always_ff @(posedge wclk_i) begin
        if (we_i) begin
            memory[waddr_i] <= wdata_i;
`ifdef SIM_LOG
            $display("ram_two_async: WRITE (%x): %x", waddr_i, wdata_i);
`endif
        end
    end

    always_ff @(posedge rclk_i) begin
        if (re_i) begin
            rdata <= memory[raddr_i];
`ifdef SIM_LOG
            $display("ram_two_async: READ  (%x): %x", raddr_i, memory[raddr_i]);
`endif
        end
    end

    assign rdata_o = rdata;

endmodule
