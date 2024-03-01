#ifndef MEMORY_H
#define MEMORY_H

#include "MemoryBankController.h"

#include <cstdint>
class Memory {
public:
    Memory(MemoryBankController* mbc) : mbcController(mbc) {};
    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t data);
    uint8_t data[65536]; // 64KB of memory
    uint8_t* getRam();

private:
    MemoryBankController* mbcController;
};

#endif