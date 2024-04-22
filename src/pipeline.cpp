/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <memory.h>
#include <iostream>
#include <iomanip>

/* CONSTRUCTOR */
Pipeline::Pipeline(Memory *m, uint32_t *binary, size_t size) {
    this->mainMemory = m;
    this->binary = binary;
    this->size = size/4;    // in dwords (instruction count)
    this->index = 0;        // dword index into the binry

    // initialize the register files - $0 is always 0 and $x = 0x100 + x
    this->registers.r[0] = 0;
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
    for(this->index = 0; this->index < this->size; this->index++) {
        // go through all 5 stages of the pipeline
        this->fetch();
        this->decode();
        this->execute();
        this->memory();
        this->writeback();

        // and one cycle is done
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
    outputPrefix();
    cout << "Clock cycle " << dec << setw(0) << this->index << ":" << endl;
    outputPrefix();
    cout << "IF/ID register (written by IF): " << endl;
    this->ifIdWrite.dump(this->index);
    cout << endl;
    outputPrefix();
    cout << "IF/ID register (read by ID): " << endl;
    this->ifIdRead.dump(this->index);
    cout << endl;

    outputPrefix();
    cout << "ID/EX register (written by ID): " << endl;
    this->idExWrite.dump(this->index);
    cout << endl;
    outputPrefix();
    cout << "ID/EX register (read by EX): " << endl;
    this->idExRead.dump(this->index);
    cout << endl;

    outputPrefix();
    cout << "EX/MEM register (written by EX): " << endl;
    this->exMemWrite.dump(this->index);
    cout << endl;
    outputPrefix();
    cout << "EX/MEM register (read by MEM): " << endl;
    this->exMemRead.dump(this->index);
    cout << endl;

    outputPrefix();
    cout << "MEM/WB register (written by MEM): " << endl;
    this->memWbWrite.dump(this->index);
    cout << endl;
    outputPrefix();
    cout << "MEM/WB register (read by WB): " << endl;
    this->memWbRead.dump(this->index);
    cout << endl;

    outputPrefix();
    cout << "User registers: " << endl;

    for(int i = 0; i < 8; i++) {    // divide the 32 regs into 4 lines of output
        outputPrefix();
        for(int j = 0; j < 4; j++) {    // with 8 regs per line
            cout << "$" << dec << setw(0) << (i*4)+j << " = 0x";
            cout << hex << uppercase << setw(8) << setfill('0') << this->registers.r[(i*4)+j];
            cout << " ";
        }

        cout << endl;
    }

    cout << endl;
}

/*
 * outputPrefix(): this is just to make the output a little prettier and easier to read
 * Parameters: none
 * Returns: nothing
 */

void Pipeline::outputPrefix() {
    cout << "[Cycle " << dec << setw(1) << this->index << "] ";
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