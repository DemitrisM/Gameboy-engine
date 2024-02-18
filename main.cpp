#include "Register.h"
#include <iostream>
using namespace std;

int main(){
    Registers reg;
    reg.setZeroFlag(true);
    reg.setSubtractFlag(true);
    reg.setHalfCarryFlag(true);
    reg.setCarryFlag(true);
    reg.BC.high = 0x12;
    cout << "Zero Flag: " << reg.getZeroFlag() << endl;
    cout << "Subtract Flag: " << reg.getSubtractFlag() << endl;
    cout << "Half Carry Flag: " << reg.getHalfCarryFlag() << endl;
    cout << "Carry Flag: " << reg.getCarryFlag() << endl;
    return 0; 
}