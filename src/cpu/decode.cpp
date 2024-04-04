/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <iostream>
#include <iomanip>

/* Instruction Decode Stage */

int Pipeline::decode() {
    // the goal is to read the instruction and set the approproiate control signals
    this->idExWrite.clear();
    this->idExWrite.newPc = this->ifIdRead.newPc;

    if(this->ifIdRead.instruction) {    // this way NOP (0x00000000) does nothing
        uint8_t opcode = this->ifIdRead.instruction >> 26;

        if(!opcode) {
            // R-format instruction
            this->idExWrite.regWrite = true;
            this->idExWrite.regDst = true;
            this->idExWrite.memToReg = false;
            this->idExWrite.memWrite = false;
            this->idExWrite.aluSrc = false;
            this->idExWrite.branch = false;
            this->idExWrite.aluOp = ALU_OP_FUNC;

            // lowest 6 bits
            this->idExWrite.function = this->ifIdRead.instruction & 0x3F;
        } else if(opcode == OPCODE_LB) {
            this->idExWrite.regWrite = true;
            this->idExWrite.regDst = false;
            this->idExWrite.memToReg = true;
            this->idExWrite.memWrite = false;
            this->idExWrite.aluSrc = true;
            this->idExWrite.branch = false;
            this->idExWrite.aluOp = ALU_OP_ADD;
        } else if(opcode == OPCODE_SB) {
            this->idExWrite.regWrite = false;
            this->idExWrite.regDst = false;     // doesn't matter here but clear anyway
            this->idExWrite.memToReg = false;   // doesn't matter here but clear anyway
            this->idExWrite.memWrite = true;
            this->idExWrite.aluSrc = true;
            this->idExWrite.branch = false;
            this->idExWrite.aluOp = ALU_OP_ADD;
        } else {
            // should undefined opcodes be handled here?
            cout << "(decode) undefined opcode 0x" << hex << uppercase << setw(2) << setfill('0') << uint32_t(opcode) << endl;
            return -1;
        }

        // register fetch
        uint32_t r1 = (this->ifIdRead.instruction >> 21) & 0x1F;
        uint32_t r2 = (this->ifIdRead.instruction >> 16) & 0x1F;
        this->idExWrite.readReg[0] = this->registers.r[r1];
        this->idExWrite.readReg[1] = this->registers.r[r2];

        // sign extend any possible offset
        this->idExWrite.signExtOffset = (this->ifIdRead.instruction) & 0xFFFF;
        if(this->idExWrite.signExtOffset & 0x8000) {
            this->idExWrite.signExtOffset |= 0xFFFF0000;    // copy highest bit into all other bits
        }

        // and indicate possible registers that may be used for writing
        this->idExWrite.writeReg15_11 = (this->ifIdRead.instruction >> 11) & 0x1F;
        this->idExWrite.writeReg20_16 = (this->ifIdRead.instruction >> 16) & 0x1F;
    }

    return 0;
}

