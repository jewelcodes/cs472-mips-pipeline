# MIPS Pipeline Emulator Project for MET CS 472
This is the third and final project for MET CS 472 (Computer Architecture) taken in spring 2024. The project implements a pipelined MIPS CPU emulation that is accurate down to the sub-instruction level. The instructions implemented are those specified in the assignment instructions: nop, lb, sb, add, and sub.

The actual pipeline main loop is in `src/pipeline.cpp` and the individual stages are in `src/cpu/`, where each stage is implemented in its own source file for clarity, cleanliness, and readability.

## Input
The helper program in `helper/` writes the instructions given in the assignment to a file called `sample.bin` that can then be used as input to the emulator. The instructions given are:
```c
{ 0xA1020000, 0x810AFFFC, 0x00831820, 0x01263820, 0x01224820, 0x81180000, 
  0x81510010, 0x00624022, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
```
While beginning work on this project, I modified the first project (MIPS disassembler) to add the lb, sb, and nop instructions, which are used in this project but not in the first. I then disassembled this sample binary before beginning work on the pipeline. This was to ease development on myself because it's easier to implement a pipeline when I know what the instructions are so I can guess what the expected output looks like. This is provided here only for completion's sake.
```asm
  9A040   sb $2, 0($8)
  9A044   lb $10, -4($8)
  9A048   add $3, $4, $3
  9A04C   add $7, $9, $6
  9A050   add $9, $9, $2
  9A054   lb $24, 0($8)
  9A058   lb $17, 16($10)
  9A05C   sub $8, $3, $2
  9A060   nop
  9A064   nop
  9A068   nop
  9A06C   nop
```
The plaintext disassembly is also in `sample.asm`.

## Output
The output is in the format specified by the assignment instructions, although I did print out the cycle number in every line to make it more readable without having to repeatedly scroll up to check which cycle it's on. The cycle numbers are **zero-based** so the first cycle is zero, and then one, and so on.

The plaintext output is in `output.txt`.
