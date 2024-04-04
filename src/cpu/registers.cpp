/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>

/* CONSTRUCTORS THAT CLEAR THE PIPELINE REGISTERS */
/* This essentially implements a NOP so we start out with nothing */

IfIdRegister::IfIdRegister() {
    this->clear();
}

IdExRegister::IdExRegister() {
    this->clear();
}

ExMemRegister::ExMemRegister() {
    this->clear();
}

MemWbRegister::MemWbRegister() {
    this->clear();
}

void IfIdRegister::clear() {
    this->instruction = 0;
    this->newPc = 0;
}

void IdExRegister::clear() {
    this->newPc = 0;
    this->regWrite = false;
    this->regDst = false;
    this->memToReg = false;
    this->memRead = false;
    this->memWrite = false;
    this->aluSrc = false;
    this->branch = false;
    this->aluOp = 0;
    this->function = 0;
}

void ExMemRegister::clear() {
    this->newPc = 0;
    this->regWrite = false;
    this->memToReg = false;
    this->memRead = false;
    this->memWrite = false;
    this->branch = false;
    this->zero = false;
}

void MemWbRegister::clear() {
    this->newPc = 0;
    this->regWrite = false;
    this->memToReg = false;
}
