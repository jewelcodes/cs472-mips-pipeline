/*
 * MET CS 472 - Computer Architecture
 * Project 3: MIPS Pipeline Emulator
 * Omar Elghoul
 */

#include <pipeline.h>
#include <memory.h>

Pipeline::Pipeline(Memory *memory, uint32_t *binary, size_t size) {
    this->memory = memory;
    this->binary = binary;
    this->size = size;
}
