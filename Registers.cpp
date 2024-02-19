#include "Registers.h"
// More predictability and less error prone
Registers::Registers() : A(0), B(0), C(0), D(0), E(0), H(0), L(0), F(0), SP(0xFFFE), PC(0x0100) {
}
void Registers::setZeroFlag(bool flag){
            if(flag){
                F |= 0x80;
            }
            else{
                F &= ~0x80;
            }
        }
void Registers::setSubtractFlag(bool flag){
            if(flag){
                F |= 0x40;
            }
            else{
                F &= ~0x40;
            }
        }
void Registers::setHalfCarryFlag(bool flag){
            if(flag){
                F |= 0x20;
            }
            else{
                F &= ~0x20;
            }
        }
void Registers::setCarryFlag(bool flag){
            if(flag){
                F |= 0x10;
            }
            else{
                F &= ~0x10;
            }
        }
bool Registers::getZeroFlag() const{
            return F & 0x80;
        }
bool Registers::getSubtractFlag() const{
            return F & 0x40;
        }
bool Registers::getHalfCarryFlag() const{
            return F & 0x20;
        }
bool Registers::getCarryFlag() const{
            return F & 0x10;
        }
// Path: main.cpp