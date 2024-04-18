/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <iostream>
#include <iomanip>

/* Instruction Memory Data Stage */

int Pipeline::memory() {
    // reset the pipeline register and then start
    this->memWbWrite.clear();
    this->memWbWrite.newPc = this->exMemRead.newPc;

    // the memory stage may or may not even happen depending on the signals
    if(this->exMemRead.memRead) {
        
    } else {
        
    }

    return 0;
}