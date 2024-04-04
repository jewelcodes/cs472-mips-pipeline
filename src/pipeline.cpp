/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <memory.h>
#include <cstring>      // memset, memmove for pipeline register files

/* CONSTRUCTOR */
Pipeline::Pipeline(Memory *memory, uint32_t *binary, size_t size) {
    this->memory = memory;
    this->binary = binary;
    this->size = size/4;    // in dwords (instruction count)
    this->index = 0;        // dword index into the binry

    // initialize the register files - $0 is always 0 and $x = 0x100 + x
    for(int i = 1; i < 32; i++) {
        this->registers.r[i] = 0x100 + i;
    }

    // reset all the control signals to start with all nops
    memset(&this->ifId, 0, sizeof(PipelineRegisters_t));
    memset(&this->idEx, 0, sizeof(PipelineRegisters_t));
    memset(&this->exMem, 0, sizeof(PipelineRegisters_t));
    memset(&this->memWb, 0, sizeof(PipelineRegisters_t));

    // the instructions don't explicitly state what PC to start with so i'm
    // choosing an arbitrary value here just to have something to dump
    this->pc = 0x800000;
}

/*
 * emulate(): main loop for the pipeline simulation
 * Parameters: none - already passed in pipeline 
 * Returns: 0 on success
 */

int Pipeline::emulate() {
    return -1;  // stub
}