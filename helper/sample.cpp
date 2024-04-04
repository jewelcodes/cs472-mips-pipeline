/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

/* Small helper program that writes the hex instructions given in the assignment into
 * a file named sample.bin so that is can be used as input for the emulator
 *
 * This is the exact same helper used in assignment 1 (MIPS disassembler) but just with
 * modified values according to this assignment
 */

#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

/* this array is directly copied from the assignment */
uint32_t instructions[] = { 0xA1020000, 0x810AFFFC, 0x00831820, 0x01263820, 0x01224820,
    0x81180000, 0x81510010, 0x00624022, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

int main(int argc, char **argv) {
    fstream file;
    file.open("sample.bin", ios::out | ios::binary);
    
    for(int i = 0; i < 12; i++) {
        file.write((const char *)&instructions[i], sizeof(uint32_t));
    }

    file.flush();
    file.close();
    return 0;
}