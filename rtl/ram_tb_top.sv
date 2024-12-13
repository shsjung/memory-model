module ram_tb_top #(
    parameter  int Width = 32,
    parameter  int Depth = 256,
    localparam int Aw    = $clog2(Depth)
) (
    input              clk1_i,
    input              clk2_i,

    input              single_we_i,
    input              single_re_i,
    input  [   Aw-1:0] single_addr_i,
    input  [Width-1:0] single_wdata_i,
    output [Width-1:0] single_rdata_o,

    input              two_sync_we_i,
    input  [   Aw-1:0] two_sync_waddr_i,
    input  [Width-1:0] two_sync_wdata_i,

    input              two_sync_re_i,
    input  [   Aw-1:0] two_sync_raddr_i,
    output [Width-1:0] two_sync_rdata_o,

    input              two_async_we_i,
    input  [   Aw-1:0] two_async_waddr_i,
    input  [Width-1:0] two_async_wdata_i,

    input              two_async_re_i,
    input  [   Aw-1:0] two_async_raddr_i,
    output [Width-1:0] two_async_rdata_o
);

    ram_single #(
        .Width (Width),
        .Depth (Depth)
    ) inst_ram_single (
        .clk_i      (clk1_i),

        .we_i       (single_we_i),
        .re_i       (single_re_i),
        .addr_i     (single_addr_i),
        .wdata_i    (single_wdata_i),
        .rdata_o    (single_rdata_o)
    );

    ram_two_sync #(
        .Width (Width),
        .Depth (Depth)
    ) inst_ram_two_sync (
        .clk_i      (clk1_i),

        .we_i       (two_sync_we_i),
        .waddr_i    (two_sync_waddr_i),
        .wdata_i    (two_sync_wdata_i),

        .re_i       (two_sync_re_i),
        .raddr_i    (two_sync_raddr_i),
        .rdata_o    (two_sync_rdata_o)
    );

    ram_two_async #(
        .Width (Width),
        .Depth (Depth)
    ) inst_ram_two_async (
        .wclk_i     (clk1_i),
        .we_i       (two_async_we_i),
        .waddr_i    (two_async_waddr_i),
        .wdata_i    (two_async_wdata_i),

        .rclk_i     (clk2_i),
        .re_i       (two_async_re_i),
        .raddr_i    (two_async_raddr_i),
        .rdata_o    (two_async_rdata_o)
    );

endmodule
