/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <iostream>
#include <iomanip>
#include <bitset>

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
    this->readReg[0] = 0;
    this->readReg[1] = 0;
    this->signExtOffset = 0;
    this->writeReg15_11 = 0;
    this->writeReg20_16 = 0;
}

void ExMemRegister::clear() {
    this->newPc = 0;
    this->regWrite = false;
    this->memToReg = false;
    this->memRead = false;
    this->memWrite = false;
    this->branch = false;
    this->zero = false;
    this->branchTarget = 0;
    this->aluResult = 0;
    this->memValue = 0;
    this->writeRegNumber = 0;
}

void MemWbRegister::clear() {
    this->newPc = 0;
    this->regWrite = false;
    this->memToReg = false;
    this->memValue = 0;
    this->aluResult = 0;
    this->writeRegNumber = 0;
}

/* Dump functions */

void PipelineRegister::outputPrefix(size_t cycle) {
    cout << "[Cycle " << dec << setw(1) << cycle << "] ";
}

void IfIdRegister::dump(size_t cycle) {
    outputPrefix(cycle);
    cout << "pc = 0x";
    cout << hex << setw(5) << setfill('0') << uppercase << this->newPc;
    cout << "  instr = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->instruction << endl;
}

void IdExRegister::dump(size_t cycle) {
    // I could kiss whoever invented the ternary operator
    outputPrefix(cycle);
    cout << "pc = 0x";
    cout << hex << setw(5) << setfill('0') << uppercase << this->newPc << endl;
    outputPrefix(cycle);
    cout << "control: ";
    cout << "regwrite=";
    cout << (this->regWrite ? "1" : "0");
    cout << "  regdst=";
    cout << (this->regDst ? "1" : "0");
    cout << "  memtoreg=";
    cout << (this->memToReg ? "1" : "0");
    cout << "  memread=";
    cout << (this->memRead ? "1" : "0");
    cout << "  memwrite=";
    cout << (this->memWrite ? "1" : "0");
    cout << "  alusrc=";
    cout << (this->aluSrc ? "1" : "0");
    cout << endl;
    outputPrefix(cycle);
    cout << "         branch=";
    cout << (this->regDst ? "1" : "0");
    cout << "    aluop=";
    bitset<2> aluOp(this->aluOp);
    cout << aluOp;
    cout << "  function=0x";
    cout << hex << setw(2) << setfill('0') << uppercase << (uint32_t)this->function;
    cout << endl;

    outputPrefix(cycle);
    cout << "reg1 = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->readReg[0];
    cout << "  reg2 = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->readReg[1];
    cout << "  seoffset = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->signExtOffset;
    cout << endl;

    outputPrefix(cycle);
    cout << "writereg_20_16 = ";
    cout << dec << setw(0) << (uint32_t)this->writeReg20_16;
    cout << "  writereg_15_11 = ";
    cout << dec << setw(0) << (uint32_t)this->writeReg15_11;

    cout << endl;
}

void ExMemRegister::dump(size_t cycle) {
    outputPrefix(cycle);
    cout << "pc = 0x";
    cout << hex << setw(5) << setfill('0') << uppercase << this->newPc << endl;

    outputPrefix(cycle);
    cout << "control: ";
    cout << "regwrite=";
    cout << (this->regWrite ? "1" : "0");
    cout << "  memtoreg=";
    cout << (this->memToReg ? "1" : "0");
    cout << "  memread=";
    cout << (this->memRead ? "1" : "0");
    cout << "  memwrite=";
    cout << (this->memWrite ? "1" : "0");
    cout << "  branch=";
    cout << (this->branch ? "1" : "0");
    cout << "  zero=";
    cout << (this->zero ? "1" : "0");
    cout << endl;

    outputPrefix(cycle);
    cout << "writereg = ";
    cout << dec << setw(0) << (uint32_t)this->writeRegNumber;
    cout << "  branchtarget = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->branchTarget;
    cout << "  aluresult = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->aluResult;
    cout << "  sw = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->memValue;

    cout << endl;
}

void MemWbRegister::dump(size_t cycle) {
    outputPrefix(cycle);
    cout << "pc = 0x";
    cout << hex << setw(5) << setfill('0') << uppercase << this->newPc << endl;

    outputPrefix(cycle);
    cout << "control: ";
    cout << "regwrite=";
    cout << (this->regWrite ? "1" : "0");
    cout << "  memtoreg=";
    cout << (this->memToReg ? "1" : "0");
    cout << endl;

    outputPrefix(cycle);
    cout << "writereg = ";
    cout << dec << setw(0) << (uint32_t)this->writeRegNumber;
    cout << "  aluresult = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->aluResult;
    cout << "  lw = 0x";
    cout << hex << setw(8) << setfill('0') << uppercase << this->memValue;

    cout << endl;
}
