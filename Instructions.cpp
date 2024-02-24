#include "Instructions.h"

void Instructions::ADD_8bit(Registers& reg, uint8_t value){
    uint16_t result = reg.A + value;
    // Set the half carry flag if the lower nibble of the sum is greater than 0x0F
    reg.setHalfCarryFlag((reg.A & 0x0F) + (value & 0x0F) > 0x0F);
    // Set the carry flag if the sum is greater than 0xFF
    reg.setCarryFlag(result > 0xFF);
    //Will handle the overflow if it occurs
    reg.A = static_cast<uint8_t>(result);
    reg.setZeroFlag(reg.A == 0);
    reg.setSubtractFlag(false);
}
void Instructions::ADD_16_bit(Registers& reg, uint16_t value){
    uint32_t result = reg.HL.reg16 + value;
    // Set the half carry flag if the lower nibble of the sum is greater than 0x0F
    reg.setHalfCarryFlag((reg.HL.reg16 & 0x0FFF) + (value & 0x0FFF) > 0x0FFF);
    // Set the carry flag if the sum is greater than 0xFFFF
    reg.setCarryFlag(result > 0xFFFF);
    //Will handle the overflow if it occurs
    reg.HL.reg16 = static_cast<uint16_t>(result);
    reg.setSubtractFlag(false);
}
void Instructions::ADC(Registers& reg, uint8_t value){
    uint16_t result = reg.A + value + reg.getCarryFlag();
    // Set the half carry flag if the lower nibble of the sum is greater than 0x0F
    reg.setHalfCarryFlag((reg.A & 0x0F) + (value & 0x0F) + reg.getCarryFlag() > 0x0F);
    // Set the carry flag if the sum is greater than 0xFF
    reg.setCarryFlag(result > 0xFF);
    //Will handle the overflow if it occurs
    reg.A = static_cast<uint8_t>(result);
    reg.setZeroFlag(reg.A == 0);
    reg.setSubtractFlag(false);
}
void Instructions::SUB(Registers& reg, uint8_t value){
    uint16_t result = reg.A - value;
    // Set the half carry flag if the lower nibble of the sum is less than the lower nibble of the value
    reg.setHalfCarryFlag((reg.A & 0x0F) < (value & 0x0F));
    // Set the carry flag if the sum is less than 0
    reg.setCarryFlag(reg.A < value);
    //Will handle the overflow if it occurs
    reg.A = static_cast<uint8_t>(result);
    reg.setZeroFlag(reg.A == 0);
    reg.setSubtractFlag(true);
}
void Instructions::SBC(Registers& reg, uint8_t value){
    uint16_t result = reg.A - value - reg.getCarryFlag();
    reg.setCarryFlag(reg.A < (value + reg.getCarryFlag()));
    // Set the half carry flag if the lower nibble of the value is less than the lower nibble of the value + carry
    reg.setHalfCarryFlag((reg.A & 0x0F) < ((value & 0x0F) + reg.getCarryFlag()));
    //Will handle the overflow if it occurs
    reg.A = static_cast<uint8_t>(result);
    reg.setZeroFlag(reg.A == 0);
    reg.setSubtractFlag(true);
}
void Instructions::INC_8bit(uint8_t& reg, Registers& flag){
    // Set the half carry flag if the lower nibble of the value is 0x0F
    flag.setHalfCarryFlag((reg & 0x0F) == 0x0F);
    //Will handle the overflow if it occurs
    reg++;
    flag.setZeroFlag(reg == 0);
    flag.setSubtractFlag(false);
}
void Instructions::INC_16bit(uint16_t& regPair){
    regPair++;
}
void Instructions::DEC_8bit(uint8_t& reg, Registers& flag){
    // Set the half carry flag if the lower nibble of the value is 0x0F
    flag.setHalfCarryFlag((reg & 0x0F) == 0x00);
    //Will handle the overflow if it occurs
    reg--;
    flag.setZeroFlag(reg == 0);
    flag.setSubtractFlag(true);
}
void Instructions::DEC_16bit(uint16_t& regPair){
    regPair--;
}
void Instructions::DAA(Registers& reg){
    uint8_t correction = 0;
    if(reg.getSubtractFlag()){
        if(reg.getHalfCarryFlag()) correction |= 0x06;
        if(reg.getCarryFlag()) correction |= 0x60;
    }
    else {
        if((reg.A & 0x0F > 0x09) || reg.getHalfCarryFlag()) correction |= 0x06;
        if(reg.A& 0xF0 > 0x90 || reg.getCarryFlag()){
            correction |= 0x60;
            reg.setCarryFlag(true);
        }   
    }   
    reg.A += reg.getSubtractFlag() ? -correction : correction;
    reg.setHalfCarryFlag(false);
    reg.setZeroFlag(reg.A == 0);
}



