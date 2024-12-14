# SystemVerilog Memory Models

This project provides SystemVerilog implementations of three commonly used types of memory modules in hardware design. These modules are designed to meet various design requirements during the hardware development process.

## Memory Models

1. **Single-port RAM**

   A memory module that supports both read and write operations, but with a single address port. Consequently, only one operation (either write or read) can be performed per clock cycle.

2. **Two-port Synchronous RAM**

   This memory type features two ports: one dedicated to write operations and the other to read operations. The separation of ports enables simultaneous write and read operations, with both ports synchronized to the same clock signal.

3. **Two-port Asynchronous RAM**

   Similar to the Two-port Synchronous RAM, this memory module also features two ports. However, each port operates in a different clock domain, making it suitable for designs that require asynchronous access.

## File Structure

- `rtl/`
  - `ram_single.sv`: Single-port RAM
  - `ram_two_sync.sv`: Two-port Synchronous RAM
  - `ram_two_async.sv`: Two-port Asynchronous RAM
  - `ram_tb_top.sv`: Top module that instantiates the three memory models for testing
- `wavedrom/`: Waveform diagrams
- `obj_dir/`: Directory containing object files and executables generated during Verilator simulation
- `tb.cpp`: Testbench top-level file
- `Makefile`: Makefile script to run the testbench
- `README.md`: Project documentation
- `LICENSE`: License information

## Running the Testbench

The provided testbench is designed for simulation using Verilator. Ensure Verilator is installed before running the testbench. Refer to the [Verilator GitHub page](https://github.com/verilator/verilator) for installation instructions.

1. Clone this repository:

   ```bash
   git clone https://github.com/shsjung/memory-model.git
   ```

2. Navigate to the `memory-model` directory and run the following command:

   ```bash
   make
   ```

## Example Waveforms

Below are example waveforms generated from the testbench simulations. These waveforms demonstrate the behavior of each memory module under different scenarios.

1. **Single-port RAM**

   The waveform shows how read and write operations are managed within a single clock cycle, where only one operation can occur at a time.

   ![Single-port RAM Waveform](https://svg.wavedrom.com/github/shsjung/memory-model/main/wavedrom/ram_single.json)

2. **Two-port Synchronous RAM**

   The waveform illustrates the simultaneous read and write operations using two distinct ports, both synchronized to the same clock signal.

   ![Two-port Synchronous RAM Waveform](https://svg.wavedrom.com/github/shsjung/memory-model/main/wavedrom/ram_two_sync.json)

3. **Two-port Asynchronous RAM**

   This memory module supports independent clock domains for its two ports. The following waveforms showcase two cases:

   - **Case 1:** Write clock is faster than read clock.

     ![Two-port Asynchronous RAM Waveform 1](https://svg.wavedrom.com/github/shsjung/memory-model/main/wavedrom/ram_two_async_1.json)

   - **Case 2:** Write clock is slower than read clock.

     ![Two-port Asynchronous RAM Waveform 2](https://svg.wavedrom.com/github/shsjung/memory-model/main/wavedrom/ram_two_async_2.json)

## License

This project is distributed under the MIT License. See the [LICENSE](./LICENSE) file for details.

## Contributions

Contributions are welcome! Please open an issue or submit a Pull Request if you'd like to contribute to this project.
