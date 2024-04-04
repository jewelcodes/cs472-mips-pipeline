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
    memset(&this->ifIdRead, 0, sizeof(PipelineRegisters_t));
    memset(&this->idExRead, 0, sizeof(PipelineRegisters_t));
    memset(&this->exMemRead, 0, sizeof(PipelineRegisters_t));
    memset(&this->memWbRead, 0, sizeof(PipelineRegisters_t));
    memset(&this->ifIdWrite, 0, sizeof(PipelineRegisters_t));
    memset(&this->idExWrite, 0, sizeof(PipelineRegisters_t));
    memset(&this->exMemWrite, 0, sizeof(PipelineRegisters_t));
    memset(&this->memWbWrite, 0, sizeof(PipelineRegisters_t));

    // the assignment doesn't explicitly state what PC to start with so i'm
    // choosing an arbitrary value here just to have something to dump
    this->pc = 0x800000;
}

/*
 * emulate(): main loop for the pipeline simulation
 * Parameters: none - already passed in pipeline 
 * Returns: 0 on success
 */

int Pipeline::emulate() {
    // each loop here corresponds to one CPU cycle
    for(size_t i = 0; i < this->size; i++) {
        this->fetch();          // go through all 5 stages of the pipeline
        /*this->decode();       // TODO!!
        this->execute();
        this->memory();
        this->writeback();*/

        this->dumpState();
        this->copyWriteToRead();
    }
}
