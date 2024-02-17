#include<iostream>
#include <cstdint>
using namespace std;

class Registers{
    public : 
        void setZeroFlag(bool flag){
            if(flag){
                F |= 0x80;
            }
            else{
                F &= ~0x80;
            }
        }
        void setSubtractFlag(bool flag){
            if(flag){
                F |= 0x40;
            }
            else{
                F &= ~0x40;
            }
        }
        void setHalfCarryFlag(bool flag){
            if(flag){
                F |= 0x20;
            }
            else{
                F &= ~0x20;
            }
        }
        void setCarryFlag(bool flag){
            if(flag){
                F |= 0x10;
            }
            else{
                F &= ~0x10;
            }
        }
        bool getZeroFlag() const{
            return F & 0x80;
        }
        bool getSubtractFlag() const{
            return F & 0x40;
        }
        bool getHalfCarryFlag() const{
            return F & 0x20;
        }
        bool getCarryFlag() const{
            return F & 0x10;
        }
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

int main(){
    cout<<"hello ";
}