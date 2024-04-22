/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <memory.h>
#include <iostream>
#include <iomanip>

/* Stage 4: Instruction Data Memory Stage */

int Pipeline::memory() {
    // reset the pipeline register and then start
    this->memWbWrite.clear();
    this->memWbWrite.newPc = this->exMemRead.newPc;

    // the memory stage may or may not even happen depending on the signals
    if(this->exMemRead.memRead) {
        this->memWbWrite.memValue = this->mainMemory->read(this->exMemRead.aluResult);
    } else if(this->exMemRead.memWrite) {
        this->mainMemory->write(this->exMemRead.aluResult, this->exMemRead.memValue);
    }

    // now simply pass the remaining signals along
    this->memWbWrite.regWrite = this->exMemRead.regWrite;
    this->memWbWrite.memToReg = this->exMemRead.memToReg;
    this->memWbWrite.writeRegNumber = this->exMemRead.writeRegNumber;
    this->memWbWrite.aluResult = this->exMemRead.aluResult;

    return 0;
}