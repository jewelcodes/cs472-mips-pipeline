/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <memory.h>

/* This is identical to the physical memory from assignment 2 (cache simulator) */

/* NOTE: This is a simulation of MEMORY and not the MEMORY STAGE of the pipeline,
 * the memory stage of the pipeline is in cpu/memory.cpp */

/* CONSTRUCTOR */
Memory::Memory(size_t size) {
    this->memory.reserve(size);
    this->size = size;

    // initialize memory according to the instructions
    for(size_t i = 0; i < size; i++) {
        this->memory[i] = (uint8_t)i & 0xFF;
    }
}

/*
 * read(): reads a byte from memory
 * Parameters: address - address of the byte to read
 * Returns: value from said address
 */

uint8_t Memory::read(uint32_t address) {
    if(address >= this->size) {
        // handle out of bounds the way real hardware is likely to do
        return 0xFF;
    } else {
        return this->memory[address];
    }
}

/*
 * write(): writes a byte to memory
 * Parameters: address - address of the byte to write
 * Parameters: data - the byte to be written
 * Returns: nothing
 */

void Memory::write(uint32_t address, uint8_t data) {
    if(address < this->size) {
        this->memory[address] = data;
    }
}
