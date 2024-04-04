/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#pragma once

#include <cstdint>      // standard integer sizes
#include <cstddef>      // size_t
#include <memory.h>

using namespace std;

/* CPU Register File */

typedef struct Registers_t {
    uint32_t r[32];     // 32x 32-bit registers
} Registers_t;

/* Pipeline Register File */

typedef struct PipelineRegisters_t {
    bool regWrite, regDst, memToReg, memRead, memWrite, ALUSrc, Branch;
    uint8_t ALUOp;      // 2-bits wide so we will fit this into a byte
} PipelineRegisters_t;

/* General CPU Class */

class Pipeline {
private:
    uint32_t *binary;
    size_t size;
    uint32_t pc;
    size_t index;

    // CPU registers
    Registers_t registers;

    // pipeline registers: IF/ID, ID/EX, EX/MEM, MEM/WB
    PipelineRegisters_t ifId, idEx, exMem, memWb;

    // main memory (simulated data cache)
    Memory *memory;

public:
    Pipeline(Memory *, uint32_t *, size_t);
    int emulate();
};
