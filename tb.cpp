#include "Vram_tb_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#define CLK1_DURATION 4
#define CLK2_DURATION 6

#define TIME_START \
    if (local_time % (CLK1_DURATION / 2) == 0) top->clk1_i = !top->clk1_i; \
    if (local_time % (CLK2_DURATION / 2) == 0) top->clk2_i = !top->clk2_i; \
    top->eval()
#define TIME_END \
    top->eval(); \
    tfp->dump(local_time++)
#define CLOCK_DELAY(x) \
    for (int xx=0; xx < x; xx++) { \
        TIME_START; \
        tfp->dump(local_time++); \
    }

int main(int argc, char **argv) {
    int clk1_pos, clk1_neg, clk2_pos, clk2_neg, local_time = 0;

    Verilated::commandArgs(argc, argv);
    Vram_tb_top* top = new Vram_tb_top;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("ram_tb_top.vcd");

    CLOCK_DELAY(12);

    printf("Test case 1 start\n");
    int single_we_i[10]    = {1, 0, 1, 1, 1, 0, 0, 0, 0};
    int single_re_i[10]    = {0, 1, 0, 0, 0, 1, 1, 1, 0};
    int single_addr_i[10]  = {0, 0, 2, 4, 3, 2, 3, 4, 0};
    int single_wdata_i[10] = {0x03020100, 0, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0, 0, 0, 0};
    clk1_pos = 0;
    while (1) {
        TIME_START;
        if (local_time % CLK1_DURATION == 0) {
            top->single_we_i = single_we_i[clk1_pos];
            top->single_re_i = single_re_i[clk1_pos];
            top->single_addr_i = single_addr_i[clk1_pos];
            top->single_wdata_i = single_wdata_i[clk1_pos];
            clk1_pos++;
        }
        TIME_END;
        if (clk1_pos == 10) {
            break;
        }
    }

    CLOCK_DELAY(24);

    printf("Test case 2 start\n");
    int two_sync_we_i[10]    = {1, 0, 1, 1, 1, 1, 0, 0, 0};
    int two_sync_waddr_i[10] = {0, 0, 2, 4, 3, 5, 0, 0, 0};
    int two_sync_wdata_i[10] = {0x13121110, 0, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x23222120, 0, 0, 0};
    int two_sync_re_i[10]    = {0, 1, 0, 1, 0, 1, 1, 1, 0};
    int two_sync_raddr_i[10] = {0, 0, 0, 2, 0, 3, 4, 5, 0};
    clk1_pos = 0;
    while (1) {
        TIME_START;
        if (local_time % CLK1_DURATION == 0) {
            top->two_sync_we_i = two_sync_we_i[clk1_pos];
            top->two_sync_waddr_i = two_sync_waddr_i[clk1_pos];
            top->two_sync_wdata_i = two_sync_wdata_i[clk1_pos];
            top->two_sync_re_i = two_sync_re_i[clk1_pos];
            top->two_sync_raddr_i = two_sync_raddr_i[clk1_pos];
            clk1_pos++;
        }
        TIME_END;
        if (clk1_pos == 10) {
            break;
        }
    }

    CLOCK_DELAY(24);

    printf("Test case 3 start\n");
    int two_async_we_i[10]    = {1, 0, 1, 1, 1, 1, 0, 0, 0};
    int two_async_waddr_i[10] = {0, 0, 2, 4, 3, 5, 0, 0, 0};
    int two_async_wdata_i[10] = {0x33323130, 0, 0x37363534, 0x3b3a3938, 0x3f3e3d3c, 0x43424140, 0, 0, 0};
    int two_async_re_i[10]    = {0, 1, 0, 1, 0, 1, 1, 1, 0};
    int two_async_raddr_i[10] = {0, 0, 0, 2, 0, 3, 4, 5, 0};
    clk1_pos = 0;
    clk2_pos = 0;
    while (1) {
        TIME_START;
        if (local_time % CLK1_DURATION == 0 && clk1_pos < 10) {
            top->two_async_we_i = two_async_we_i[clk1_pos];
            top->two_async_waddr_i = two_async_waddr_i[clk1_pos];
            top->two_async_wdata_i = two_async_wdata_i[clk1_pos];
            clk1_pos++;
        }
        if (local_time % CLK2_DURATION == 0 && clk2_pos < 10) {
            top->two_async_re_i = two_async_re_i[clk2_pos];
            top->two_async_raddr_i = two_async_raddr_i[clk2_pos];
            clk2_pos++;
        }
        TIME_END;
        if (clk1_pos == 10 && clk2_pos == 10) {
            break;
        }
    }

    CLOCK_DELAY(24);
    printf("Test finished\n");

    tfp->close();
    delete top;
    delete tfp;
    return 0;

}
