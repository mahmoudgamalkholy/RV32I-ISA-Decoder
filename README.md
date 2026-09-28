```markdown
# RV32I ISA Decoder: Quick Reference Guide

This file contains the basic commands for generating test files, compiling the project, running the decoder, and executing tests. It follows the natural workflow of the project.

## 1. Generating ELF and Assembly Files (Preparation)

To test the decoder, you first need an ELF file. You can create files compatible with the RV32I architecture from C/C++ code using the RISC-V GNU Toolchain.

**A. To convert C/C++ code into an executable ELF file (`.elf`):**

```bash
riscv64-unknown-elf-g++ -march=rv32i -mabi=ilp32 source_code.cpp -o test.elf

```

*(Note: Using `-march=rv32i` ensures that the compiler generates instructions strictly compatible with your decoder, which supports the Base Integer Instructions only).*

**B. To convert C/C++ code into an Assembly file (`.s`) for reference:**

```bash
riscv64-unknown-elf-g++ -march=rv32i -mabi=ilp32 -S source_code.cpp -o output.s

```

## 2. Compiling the Decoder (Build)

To compile the core code (`decoder.cpp` and `instruction.hpp`) and generate the `decoder` executable, run the following command in the terminal:

```bash
make

```

## 3. Running the Decoder on the ELF File (Execution)

After building the program, use it to decode your generated `.elf` file and print the assembly instructions to the terminal:

```bash
./decoder ./test.elf

```

*(Replace `./test.elf` with the actual path and name of the file you want to decode).*

## 4. Running Tests (Validation)

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

## 5. Cleaning the Workspace

To remove the generated executable files (`decoder` and `run_tests`) and start with a clean directory:

```bash
make clean

```

```


```bash
git add README.md
git commit -m "Fix markdown formatting for code blocks"
git push origin main

```
