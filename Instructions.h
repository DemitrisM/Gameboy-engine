#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include "Registers.h"

class Instructions{
    public:
        void ADD(Registers& reg, uint8_t value);
        void ADD(Registers& reg, uint16_t value);
        void ADC(Registers& reg, uint8_t value);
    private:
};

#endif
// Path: main.cpp
