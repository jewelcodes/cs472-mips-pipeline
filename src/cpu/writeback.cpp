/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>

/* Stage 5: Instruction Writeback Stage */

int Pipeline::writeback() {
    // the writeback is the last stage of the pipeline so it does not write
    // to any pipeline registers, all it does is write to the general purpose
    // registers according to the control signals

    uint32_t value;
    if(this->memWbRead.regWrite) {
        if(this->memWbRead.memToReg) {
            value = this->memWbRead.memValue;   // for loads
        } else {
            value = this->memWbRead.aluResult;  // R-type instructions
        }

        this->registers.r[this->memWbRead.writeRegNumber] = value;
    }

    return 0;
}