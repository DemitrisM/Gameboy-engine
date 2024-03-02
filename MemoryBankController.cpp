#include "MemoryBankController.h"
#include "Memory.h"
#include<fstream>
#include<vector>

//Recheck file to see if there is a missing implementation like rumble or RTC

class NoMBC : public MemoryBankController {
public:
    NoMBC(Memory* memory) : memory(memory) {}

    uint8_t read(uint16_t address) const override {
        return memory->data[address];
    }

    void write(uint16_t address, uint8_t value) override {
        memory->data[address] = value;
    }

private:
    Memory* memory;
};  // Add a semicolon here

class MBC1 : public MemoryBankController {
public:
    MBC1(Memory* memory) : memory(memory), romBank(1), ramBank(0), ramEnabled(false), mode(0) {}

    uint8_t read(uint16_t address) const override {
        if (address < 0x4000) {
            // Always access the first ROM bank
            return memory->data[address];
        } else if (address < 0x8000) {
            // Access the selected ROM bank
            return memory->data[0x4000 * romBank + (address - 0x4000)];
        } else if (address >= 0xA000 && address < 0xC000) {
            // Access the selected RAM bank, if RAM is enabled
            return ramEnabled ? memory->data[0xA000 * ramBank + (address - 0xA000)] : 0xFF;
        }
        return 0xFF;
    }

    void write(uint16_t address, uint8_t value) override {
        if (address < 0x2000) {
            // Enable or disable RAM
            ramEnabled = (value & 0x0A) == 0x0A;
        } else if (address < 0x4000) {
            // Select the lower 5 bits of the ROM bank number
            romBank = (romBank & 0x60) | (value & 0x1F);
            if (romBank == 0) romBank = 1;
        } else if (address < 0x6000) {
            if (mode == 0) {
                // In ROM banking mode, select the upper 2 bits of the ROM bank number
                romBank = (romBank & 0x1F) | ((value & 0x03) << 5);
            } else {
                // In RAM banking mode, select the RAM bank number
                ramBank = value & 0x03;
            }
        } else if (address < 0x8000) {
            // Select the banking mode
            mode = value & 0x01;
        } else if (address >= 0xA000 && address < 0xC000) {
            // Write to the selected RAM bank, if RAM is enabled
            if (ramEnabled) memory->data[0xA000 * ramBank + (address - 0xA000)] = value;
        }
    }

private:
    Memory* memory;
    uint8_t romBank;
    uint8_t ramBank;
    bool ramEnabled;
    uint8_t mode;
};

class MBC2 : public MemoryBankController {
public:
    MBC2(Memory* memory) : memory(memory), romBank(1), ramEnabled(false) {}

    uint8_t read(uint16_t address) const override {
        if (address < 0x4000) {
            // Always access the first ROM bank
            return memory->data[address];
        } else if (address < 0x8000) {
            // Access the selected ROM bank
            return memory->data[0x4000 * romBank + (address - 0x4000)];
        } else if (address >= 0xA000 && address < 0xA200) {
            // Access the RAM bank, if RAM is enabled
            return ramEnabled ? memory->data[0xA000 + (address - 0xA000)] : 0xFF;
        }
        return 0xFF;
    }

    void write(uint16_t address, uint8_t value) override {
        if (address < 0x2000) {
            // Enable or disable RAM, but only if the least significant bit of the upper address byte is 0
            if ((address & 0x0100) == 0) {
                ramEnabled = (value & 0x0F) == 0x0A;
            }
        } else if (address < 0x4000) {
            // Select the ROM bank number, but only if the least significant bit of the upper address byte is 1
            if ((address & 0x0100) == 0x0100) {
                romBank = value & 0x0F;
                if (romBank == 0) romBank = 1;
            }
        } else if (address >= 0xA000 && address < 0xA200) {
            // Write to the RAM bank, if RAM is enabled
            if (ramEnabled) memory->data[0xA000 + (address - 0xA000)] = value & 0x0F;
        }
    }

private:
    Memory* memory;
    uint8_t romBank;
    bool ramEnabled;
};

//No clock feature yet, needs implementation
class MBC3 : public MemoryBankController {
public:
    MBC3(Memory* memory) : memory(memory), romBank(1), ramBank(0), ramEnabled(false) {}

    uint8_t read(uint16_t address) const override {
        if (address < 0x4000) {
            // Always access the first ROM bank
            return memory->read(address);
        } else if (address < 0x8000) {
            // Access the selected ROM bank
            return memory->read(0x4000 * romBank + (address - 0x4000));
        } else if (address >= 0xA000 && address < 0xC000) {
            // Access the selected RAM bank, if RAM is enabled
            return ramEnabled ? memory->read(0x2000 * ramBank + (address - 0xA000)) : 0xFF;
        }
        return 0xFF;
    }

    void write(uint16_t address, uint8_t value) override {
        if (address < 0x2000) {
            // Enable or disable RAM
            ramEnabled = (value & 0x0A) == 0x0A;
        } else if (address < 0x4000) {
            // Select the ROM bank number
            romBank = value & 0x7F;
            if (romBank == 0) romBank = 1;
        } else if (address < 0x6000) {
            // Select the RAM bank number
            ramBank = value & 0x03;
        } else if (address >= 0xA000 && address < 0xC000) {
            // Write to the selected RAM bank, if RAM is enabled
            if (ramEnabled) memory->write(0x2000 * ramBank + (address - 0xA000), value);
        }
    }

private:
    Memory* memory;
    uint8_t romBank;
    uint8_t ramBank;
    bool ramEnabled;
};

class MBC5 : public MemoryBankController {
public:
    MBC5(Memory* memory) : memory(memory), romBank(1), ramBank(0), ramEnabled(false), ram(memory->getRam()) {}

    uint8_t read(uint16_t address) const override {
        if (address < 0x4000) {
            return memory->read(address);
        } else if (address < 0x8000) {
            return memory->read(0x4000 * romBank + (address - 0x4000));
        } else if (address >= 0xA000 && address < 0xC000) {
            return ramEnabled ? ram[0x2000 * ramBank + (address - 0xA000)] : 0xFF;
        }
        return 0xFF;
    }

    void write(uint16_t address, uint8_t value) override {
        if (address < 0x2000) {
            ramEnabled = (value & 0x0A) == 0x0A;
        } else if (address < 0x3000) {
            romBank = (romBank & 0x100) | value;
        } else if (address < 0x4000) {
            romBank = (romBank & 0xFF) | ((value & 0x01) << 8);
        } else if (address < 0x6000) {
            ramBank = value & 0x0F;
        } else if (address >= 0xA000 && address < 0xC000) {
            if (ramEnabled) ram[0x2000 * ramBank + (address - 0xA000)] = value;
        }
    }

    void saveRAM(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        file.write(reinterpret_cast<char*>(ram), 0x2000 * ramBank);
    }

    void loadRAM(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        file.read(reinterpret_cast<char*>(ram), 0x2000 * ramBank);
    }

private:
    Memory* memory;
    uint16_t romBank;
    uint8_t ramBank;
    bool ramEnabled;
    uint8_t* ram;
};

class MBC7 : public MemoryBankController {
public:
    MBC7(Memory* memory) : memory(memory), romBank(1), ramEnabled(false), sensorX(0), sensorY(0) {}

    uint8_t read(uint16_t address) const override {
        if (address < 0x4000) {
            return memory->data[address];
        } else if (address < 0x8000) {
            return memory->data[0x4000 * romBank + (address - 0x4000)];
        } else if (address >= 0xA000 && address < 0xA200) {
            return ramEnabled ? memory->data[0xA000 + (address - 0xA000)] : 0xFF;
        } else if (address >= 0x8000 && address < 0x9000) {
            // Read sensor data
            return (sensorX << 4) | sensorY;
        }
        return 0xFF;
    }

    void write(uint16_t address, uint8_t value) override {
        if (address < 0x2000) {
            ramEnabled = (value & 0x0A) == 0x0A;
        } else if (address < 0x4000) {
            romBank = value & 0x7F;
            if (romBank == 0) romBank = 1;
        } else if (address >= 0xA000 && address < 0xA200) {
            if (ramEnabled) memory->data[0xA000 + (address - 0xA000)] = value & 0x0F;
        } else if (address >= 0x4000 && address < 0x6000) {
            // Write to sensor
            sensorX = (value >> 4) & 0x0F;
            sensorY = value & 0x0F;
        }
    }

private:
    Memory* memory;
    uint8_t romBank;
    bool ramEnabled;
    uint8_t sensorX;
    uint8_t sensorY;
};


// Path: MemoryBankController.h