/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <iostream>
#include <fstream>
#include <pipeline.h>
#include <memory.h>

using namespace std;

int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "usage: " << argv[0] << " input_file.bin" << endl;
        return -1;
    }

    // load the file specified in the arguments
    ifstream file(argv[1], ios::in | ios::binary | ios::ate);
    size_t size = file.tellg();     // file size
    file.clear();
    file.seekg(0);

    vector<char> buffer(size);
    file.read(buffer.data(), size);

    // create memory
    Memory m(1024);

    // create instance of pipeline
    Pipeline p(&m, (uint32_t *)buffer.data(), size);
    return p.emulate();
}
