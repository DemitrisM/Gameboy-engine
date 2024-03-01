#include "Memory.h"

uint8_t Memory::read(uint16_t addr) const {
    return mbcController->read(addr);
}

void Memory::write(uint16_t addr, uint8_t data) {
    mbcController->write(addr, data);
}

uint8_t* Memory::getRam() {
    return data;
}