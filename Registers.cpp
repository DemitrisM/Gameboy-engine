#include "Register.h"

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