/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <iostream>
#include <iomanip>

/* Instruction Execute Stage */

int Pipeline::execute() {
    this->exMemWrite.clear();
    this->exMemWrite.newPc = this->idExRead.newPc;
}
