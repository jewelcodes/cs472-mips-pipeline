/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>

/* Instruction Fetch Stage */

int Pipeline::fetch() {
    // that's literally all there is to this
    this->ifIdWrite.newPc = this->pc + 4;
    this->ifIdWrite.instruction = this->binary[this->index];
}
