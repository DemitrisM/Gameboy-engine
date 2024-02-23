#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include "Registers.h"

class Instructions{
    public:
        //8 and 16 bit ADD
        void ADD(Registers& reg, uint8_t value);
        void ADD(Registers& reg, uint16_t value);
        void ADC(Registers& reg, uint8_t value);
        void SUB(Registers& reg, uint8_t value);
        void SBC(Registers& reg, uint8_t value);
        //8 and 16 bit INC
        void INC(uint8_t& reg, Registers& flag);
        void INC(uint16_t& regPair);
        //8 and 16 bit DEC
        void DEC(uint8_t& reg, Registers& flag);
        void DEC(uint16_t& regPair);
        void DAA(Registers& reg);
    private:
};

#endif
// Path: main.cpp
