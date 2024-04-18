/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <memory.h>
#include <cstring>      // memset, memmove for pipeline register files
#include <iostream>
#include <iomanip>

/* CONSTRUCTOR */
Pipeline::Pipeline(Memory *m, uint32_t *binary, size_t size) {
    this->mainMemory = m;
    this->binary = binary;
    this->size = size/4;    // in dwords (instruction count)
    this->index = 0;        // dword index into the binry

    // initialize the register files - $0 is always 0 and $x = 0x100 + x
    for(int i = 1; i < 32; i++) {
        this->registers.r[i] = 0x100 + i;
    }

    // the assignment doesn't explicitly state what PC to start with so i'm
    // choosing a nice value to dump
    this->pc = 0x00000;
}

/*
 * emulate(): main loop for the pipeline simulation
 * Parameters: none - already passed in pipeline 
 * Returns: 0 on success
 */

int Pipeline::emulate() {
    // each loop here corresponds to one CPU cycle
    // TEMPORARILY ONLY DO ONE CYCLE UNTIL I GET IT WORKING
    for(this->index = 0; this->index < 4; this->index++) {
        this->fetch();          // go through all 5 stages of the pipeline
        this->decode();
        this->execute();
        this->memory();
        //this->writeback();

        this->dumpState();
        this->copyWriteToRead();
    }

    return 0;
}

/*
 * dumpState(): dumps all the pipeline registers
 * Parameters: none
 * Returns: nothing
 */

void Pipeline::dumpState() {
    cout << "Clock cycle " << dec << this->index << ":" << endl;
    cout << "IF/ID register (written by IF): " << endl;
    this->ifIdWrite.dump();
    cout << endl << "IF/ID register (read by ID): " << endl;
    this->ifIdRead.dump();
    cout << endl;

    cout << "ID/EX register (written by ID): " << endl;
    this->idExWrite.dump();
    cout << endl << "ID/EX register (read by EX): " << endl;
    this->idExRead.dump();
    cout << endl;

    cout << "EX/MEM register (written by EX): " << endl;
    this->exMemWrite.dump();
    cout << endl << "EX/MEM register (read by MEM): " << endl;
    this->exMemRead.dump();
    cout << endl;

    cout << "MEM/WB register (written by MEM): " << endl;
    this->memWbWrite.dump();
    cout << endl << "MEM/WB register (read by MEM): " << endl;
    this->memWbRead.dump();
    cout << endl;
}

/*
 * copyWriteToRead(): copies the write registers to the read registers and clears out the write ones
 * Parameters: none
 * Returns: nothing
 */

void Pipeline::copyWriteToRead() {
    this->ifIdRead = this->ifIdWrite;
    this->idExRead = this->idExWrite;
    this->exMemRead = this->exMemWrite;
    this->memWbRead = this->memWbWrite;

    this->ifIdWrite = IfIdRegister();
    this->idExWrite = IdExRegister();
    this->exMemWrite = ExMemRegister();
    this->memWbWrite = MemWbRegister();

    this->pc = this->ifIdRead.newPc;    // TODO: change this to the final thing in MemWb instead when done
}