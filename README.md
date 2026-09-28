```markdown
# RV32I ISA Decoder: Quick Reference Guide

This file contains the basic commands for compiling, running, and testing the project, as well as instructions for generating test files.

## 1. Compiling the Decoder
To compile the core code (`decoder.cpp` and `instruction.hpp`) and generate the `decoder` executable, run the following command in the terminal:

```bash
make

```

## 2. Running the Decoder on an ELF File

After building the program, you can use it to decode any `.elf` file and print the assembly instructions to the terminal using this command:

```bash
./decoder ./test.elf

```

*(Replace `./test.elf` with the actual path and name of the file you want to decode).*

## 3. Running Tests

**A. Unit Tests (using Google Test):**
To compile and execute the unit tests verifying the mathematical decoding logic, run these two commands:

```bash
make test
./run_tests

```

**B. Regression Tests (using LIT):**
To compare the current program's output against the baseline results and ensure no new bugs were introduced, execute:

```bash
make test_lit

```

## 4. Generating ELF and Assembly Files from C/C++ Code

To create files compatible with the RV32I architecture for testing in your decoder, you must use the RISC-V GNU Toolchain compiler.

**A. To convert C/C++ code into an Assembly file (`.s`):**

```bash
riscv64-unknown-elf-g++ -march=rv32i -mabi=ilp32 -S source_code.cpp -o output.s

```

**B. To convert C/C++ code into an executable ELF file (`.elf`):**

```bash
riscv64-unknown-elf-g++ -march=rv32i -mabi=ilp32 source_code.cpp -o test.elf

```

*(Note: Using `-march=rv32i` ensures that the compiler generates instructions strictly compatible with your decoder, which supports the Base Integer Instructions only).*

## 5. Cleaning the Workspace

To remove the generated executable files (`decoder` and `run_tests`) and start with a clean directory:

```bash
make clean

```


