#ifndef REGISTER_H
#define REGISTER_H
#include <cstdint>

class Registers{
    public : 
        void setZeroFlag(bool flag);
        void setSubtractFlag(bool flag);
        void setHalfCarryFlag(bool flag);
        void setCarryFlag(bool flag);
        bool getZeroFlag() const;
        bool getSubtractFlag() const;
        bool getHalfCarryFlag() const;
        bool getCarryFlag() const;
    private :
        uint8_t A, B, C, D, E, H, L, F;
        // Stack Pointer and Program Counter
        uint16_t SP, PC;
        // Register Pair below
        uint16_t BC, DE, HL;
};
union RegisterPair{
    //set low and high 8 bit registers or 16 bit register
    uint16_t reg16;
    struct{
        uint8_t low;
        uint8_t high;
    };
};
#endif
// Path: Registers.cpp