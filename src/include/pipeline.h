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

/* Pipeline Register Files */

class IfIdRegister {
public:
    uint32_t newPc;
    uint32_t instruction;

    IfIdRegister();
    void dump();
    void clear();
};

class IdExRegister {
public:
    uint32_t newPc;
    bool regWrite, regDst, memToReg, memRead, memWrite, aluSrc, branch;
    uint8_t aluOp, function;
    uint32_t readReg[2];
    uint32_t signExtOffset;
    uint8_t writeReg20_16, writeReg15_11;

    IdExRegister();
    void dump();
    void clear();
};

class ExMemRegister {
public:
    uint32_t newPc;
    bool regWrite, memToReg, memRead, memWrite, branch, zero;
    uint32_t branchTarget, aluResult, memValue;
    uint8_t writeRegNumber;

    ExMemRegister();
    void dump();
    void clear();
};

class MemWbRegister {
public:
    uint32_t newPc;
    bool regWrite, memToReg;
    uint32_t memValue, aluResult;
    uint8_t writeRegNumber;

    MemWbRegister();
    void dump();
    void clear();
};

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
    // one read and one write copy of each 
    IfIdRegister ifIdRead, ifIdWrite;
    IdExRegister idExRead, idExWrite;
    ExMemRegister exMemRead, exMemWrite;
    MemWbRegister memWbRead, memWbWrite;

    // main memory (simulated data cache)
    Memory *mainMemory;

    // individual stages of the pipeline
    int fetch();
    int decode();
    int execute();
    int memory();
    int writeback();

public:
    Pipeline(Memory *, uint32_t *, size_t);
    int emulate();
    void dumpState();
    void copyWriteToRead();
};
