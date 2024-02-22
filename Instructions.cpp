#include "Instructions.h"

void Instructions::ADD(Registers& reg, uint8_t value){
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
void Instructions::ADD(Registers& reg, uint16_t value){
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
    reg.setCarryFlag(result > 0xFF);
    //Will handle the overflow if it occurs
    reg.A = static_cast<uint8_t>(result);
    reg.setZeroFlag(reg.A == 0);
    reg.setSubtractFlag(true);
}
void Instructions::SBC(Registers& reg, uint8_t value){
    uint16_t result = reg.A - value - reg.getCarryFlag();
    // Set the half carry flag if the lower nibble of the sum is less than the lower nibble of the value
    reg.setHalfCarryFlag((reg.A & 0x0F) < (value & 0x0F) + reg.getCarryFlag());
    // Set the carry flag if the sum is less than 0
    reg.setCarryFlag(result > 0xFF);
    //Will handle the overflow if it occurs
    reg.A = static_cast<uint8_t>(result);
    reg.setZeroFlag(reg.A == 0);
    reg.setSubtractFlag(true);
}
void Instructions::INC(uint8_t& reg, Registers& flag){
    // Set the half carry flag if the lower nibble of the value is 0x0F
    flag.setHalfCarryFlag((reg & 0x0F) == 0x0F);
    //Will handle the overflow if it occurs
    reg++;
    flag.setZeroFlag(reg == 0);
    flag.setSubtractFlag(false);
}

