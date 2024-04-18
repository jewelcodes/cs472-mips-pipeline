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

    // some fields must be calculated regardless of what the instruction is
    uint32_t offset = this->idExRead.signExtOffset;
    if(offset & 0x80000000) {   // check for negative
        offset = (~offset)+1;
        offset <<= 2;
        this->exMemWrite.branchTarget = this->exMemWrite.newPc - offset;
    } else {
        offset <<= 2;
        this->exMemWrite.branchTarget = this->exMemWrite.newPc + offset;
    }

    // determine write register number
    if(this->idExRead.regDst) {
        this->exMemWrite.writeRegNumber = this->idExRead.writeReg15_11;
    } else {
        this->exMemWrite.writeRegNumber = this->idExRead.writeReg20_16;
    }

    // ALU component -- first determine the inputs
    uint32_t input1, input2;
    input1 = this->idExRead.readReg[0];
    if(this->idExRead.aluSrc) {
        // aluSrc == 1: one register, and one sign-extended value are inputs to the ALU
        input2 = this->idExRead.signExtOffset;
    } else {
        input2 = this->idExRead.readReg[1];
    }

    // now determine what the ALU is doing at all
    switch(this->idExRead.aluOp) {
    case ALU_OP_ADD:
        this->exMemWrite.aluResult = input1 + input2;
        break;
    case ALU_OP_SUB:
        this->exMemWrite.aluResult = input1 - input2;
        break;
    case ALU_OP_FUNC:
    default:
        switch(this->idExRead.function) {
        case FUNCTION_ADD:
            this->exMemWrite.aluResult = input1 + input2;
            break;
        case FUNCTION_SUB:
            this->exMemWrite.aluResult = input1 - input2;
            break;
        default:
            cout << "undefined ALU function code: 0x" << hex << uppercase << (uint32_t)this->idExRead.function << endl;
            return -1;
        }
    }

    // set the ALU's zero flag appropriately
    this->exMemWrite.zero = (this->exMemWrite.aluResult == 0);

    // the remaining signals aren't used by the ALU; they can just be copied for the next stage
    this->exMemWrite.regWrite = this->idExRead.regWrite;
    this->exMemWrite.memToReg = this->idExRead.memToReg;
    this->exMemWrite.memRead = this->idExRead.memRead;
    this->exMemWrite.memWrite = this->idExRead.memWrite;
    this->exMemWrite.branch = this->idExRead.branch;
}
