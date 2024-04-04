/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#pragma once

#include <cstdint>      // standard integer sizes
#include <cstddef>      // size_t
#include <vector>       // for memory simulation

using namespace std;

class Memory {
private:
    vector<uint8_t> memory;    // where we'll store the memory
    size_t size;

public:
    Memory(size_t);
    uint8_t read(uint32_t);
    void write(uint32_t, uint8_t);
};
