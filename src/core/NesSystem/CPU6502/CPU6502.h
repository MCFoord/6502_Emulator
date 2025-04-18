#pragma once

#include <stdint.h>
#include <vector>
#include <string>

class Bus;

class CPU6502
{
public:
    CPU6502();
    ~CPU6502();

    //registers
    uint8_t a = 0x00;
    uint8_t x = 0x00;
    uint8_t y = 0x00;
    uint8_t sp = 0x00;
    uint16_t pc = 0x000;
    uint8_t status = 0x00;

    struct instruction
    {
        uint8_t opcode;
        std::string instructionName;
        std::string addressingModeName;
        void (CPU6502::*addressingMode)();
        void (CPU6502::*operation)();
        uint8_t cycles;
    };

    uint16_t currentAddress = 0x000;
    uint8_t currentValue = 0x00;
    instruction currentInstruction;
    uint8_t cycles = 0;

    

    enum CPUFLAGS
    {
        C = (1 << 0),
        Z = (1 << 1),
        I = (1 << 2),
        D = (1 << 3),
        B = (1 << 4),
        U = (1 << 5),
        V = (1 << 6),
        N = (1 << 7)
    };

    void connectBus(Bus *b);

    bool getFlag(CPUFLAGS flag);
    void setFlag(CPUFLAGS flag, bool set);

    void fetch();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);

    void push(uint8_t value);
    uint8_t pop();

    void reset();
    void tick();
    void execute();
    void run(int numOperations);
    void run(bool& shouldStop);
    void run(bool& shouldStop, const std::vector<int> breakpoints);
    void run();
    

    //debug methods
    std::string registerToString();
    std::string instructionInfoToString();
    std::string statusToString();
    void printOperation(uint16_t address, std::ostream& output);
    void run(std::ostream& output, int numOperations);
    void execute(std::ostream& output);

private:
    Bus *bus = nullptr;

    //addressing modes
    void implicit();
    void immediate();
    void accumulator();
    void relative();

    void indirect();
    void indirectX();
    void indirectY();

    void absolute();
    void absoluteX();
    void absoluteY();

    void zeroPage();
    void zeroPageX();
    void zeroPageY();

    //interrupts
    void NMI();
    void IRQ();

    //instructions
    void ADC();
    void AND();
    void ASL();
    void BCC();
    void BCS();
    void BEQ();
    void BIT();
    void BMI();
    void BNE();
    void BPL();
    void BRK();
    void BVC();
    void BVS();
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void CMP();
    void CPX();
    void CPY();
    void DEC();
    void DEX();
    void DEY();
    void EOR();
    void INC();
    void INX();
    void INY();
    void JMP();
    void JSR();
    void LDA();
    void LDX();
    void LDY();
    void LSR();
    void NOP();
    void ORA();
    void PHA();
    void PHP();
    void PLA();
    void PLP();
    void ROL();
    void ROR();
    void RTI();
    void RTS();
    void SBC();
    void SEC();
    void SED();
    void SEI();
    void STA();
    void STX();
    void STY();
    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();
    void ILL(); //illegal opcodes

    std::vector<instruction> instructions;
};
