#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include "Registers.h"

class Instructions{
    public:
        void ADD(Registers& reg, uint8_t value);
        void ADD(Registers& reg, uint16_t value);
        void ADC(Registers& reg, uint8_t value);
        void SUB(Registers& reg, uint8_t value);
        void SBC(Registers& reg, uint8_t value);
        void INC(uint8_t& reg, Registers& flag);
    private:
};

#endif
// Path: main.cpp
