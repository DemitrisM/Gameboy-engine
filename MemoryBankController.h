#ifndef MEMORYBANKCONTROLLER_H
#define MEMORYBANKCONTROLLER_H

#include <cstdint>

class MemoryBankController {
public:
    virtual ~MemoryBankController() = default;
    virtual uint8_t read(uint16_t address) const = 0;
    virtual void write(uint16_t address, uint8_t value) = 0;
};

#endif // MEMORYBANKCONTROLLER_H
