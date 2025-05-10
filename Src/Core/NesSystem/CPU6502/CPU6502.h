#pragma once

#include <memory>
#include <stdint.h>
#include <vector>
#include <string>
#include "Bus.h"
#include "PPU.h"

struct CPUState
{
    uint8_t A = 0;
    uint8_t X = 0;
    uint8_t Y = 0;
    uint8_t SP = 0;
    uint16_t PC = 0;
    bool C = false;
    bool Z = false;
    bool I = false;
    bool D = false;
    bool B = false;
    bool U = false;
    bool V = false;
    bool N = false;
    uint8_t opcode = 0;
    uint8_t instructionCycle = 0;
    std::string instructionName = "";
    std::string addressingModeName = "";
    uint8_t currentValue = 0;
    uint16_t currentAddress = 0;
};

class CPU6502
{
public:
    CPU6502();
    ~CPU6502();

    void connectBus(std::shared_ptr<Bus> bus) { m_bus = bus; }
    void connectPPU(std::shared_ptr<PPU> PPU) { m_PPU = PPU; }
    bool tick();
    void reset();
    CPUState getCPUState()
    {
        return CPUState
        {
            .A = A,
            .X = X,
            .Y = Y,
            .SP = SP,
            .PC = PC,
            .C = getFlag(CPUFLAGS::C),
            .Z = getFlag(CPUFLAGS::Z),
            .I = getFlag(CPUFLAGS::I),
            .D = getFlag(CPUFLAGS::D),
            .B = getFlag(CPUFLAGS::B),
            .U = getFlag(CPUFLAGS::U),
            .V = getFlag(CPUFLAGS::V),
            .N = getFlag(CPUFLAGS::N),
            .opcode = m_currentInstruction.opcode,
            .instructionCycle = m_instructionCycleCount,
            .instructionName = m_currentInstruction.instructionName,
            .addressingModeName = m_currentInstruction.addressingModeName,
            .currentValue = m_currentValue,
            .currentAddress = m_currentAddress
        };
    }

private:
    //registers
    uint8_t A = 0x00;
    uint8_t X = 0x00;
    uint8_t Y = 0x00;
    uint8_t SP = 0x00;
    uint16_t PC = 0x0000;
    uint8_t STATUS = 0x00;

    struct instruction
    {
        uint8_t opcode;
        std::string instructionName;
        std::string addressingModeName;
        bool (CPU6502::*addressingMode)(uint8_t cycle);
        bool (CPU6502::*operation)(uint8_t cycle);
        uint64_t cycles;
    };

    bool m_inResetState = true;
    uint16_t m_currentAddress = 0x0000;
    uint16_t m_addressingPointer = 0x0000;
    uint8_t m_currentValue = 0x00;
    instruction m_currentInstruction;
    uint8_t m_instructionCycleCount = 1;
    uint8_t m_internalCycleCount = 1;

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

    instruction peek() { return instructions[read(PC)]; }
    void fetch();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
    void push(uint8_t value);
    uint8_t pop();
    bool getFlag(CPUFLAGS flag);
    void setFlag(CPUFLAGS flag, bool set);

    std::shared_ptr<Bus> m_bus = nullptr;
    std::shared_ptr<PPU> m_PPU = nullptr;

    //addressing modes
    bool implicit(uint8_t cycle);
    bool immediate(uint8_t cycle);
    bool accumulator(uint8_t cycle);
    bool relative(uint8_t cycle);

    bool indirect(uint8_t cycle);
    bool indirectX(uint8_t cycle);
    bool indirectY(uint8_t cycle);

    bool absolute(uint8_t cycle);
    bool absoluteX(uint8_t cycle);
    bool absoluteY(uint8_t cycle);

    bool zeroPage(uint8_t cycle);
    bool zeroPageX(uint8_t cycle);
    bool zeroPageY(uint8_t cycle);

    //interrupts
    bool NMI(uint8_t cycle);
    bool IRQ(uint8_t cycle);

    //instructions
    bool ADC(uint8_t cycle);
    bool AND(uint8_t cycle);
    bool ASL(uint8_t cycle);
    bool BCC(uint8_t cycle);
    bool BCS(uint8_t cycle);
    bool BEQ(uint8_t cycle);
    bool BIT(uint8_t cycle);
    bool BMI(uint8_t cycle);
    bool BNE(uint8_t cycle);
    bool BPL(uint8_t cycle);
    bool BRK(uint8_t cycle);
    bool BVC(uint8_t cycle);
    bool BVS(uint8_t cycle);
    bool CLC(uint8_t cycle);
    bool CLD(uint8_t cycle);
    bool CLI(uint8_t cycle);
    bool CLV(uint8_t cycle);
    bool CMP(uint8_t cycle);
    bool CPX(uint8_t cycle);
    bool CPY(uint8_t cycle);
    bool DEC(uint8_t cycle);
    bool DEX(uint8_t cycle);
    bool DEY(uint8_t cycle);
    bool EOR(uint8_t cycle);
    bool INC(uint8_t cycle);
    bool INX(uint8_t cycle);
    bool INY(uint8_t cycle);
    bool JMP(uint8_t cycle);
    bool JSR(uint8_t cycle);
    bool LDA(uint8_t cycle);
    bool LDX(uint8_t cycle);
    bool LDY(uint8_t cycle);
    bool LSR(uint8_t cycle);
    bool NOP(uint8_t cycle);
    bool ORA(uint8_t cycle);
    bool PHA(uint8_t cycle);
    bool PHP(uint8_t cycle);
    bool PLA(uint8_t cycle);
    bool PLP(uint8_t cycle);
    bool ROL(uint8_t cycle);
    bool ROR(uint8_t cycle);
    bool RTI(uint8_t cycle);
    bool RTS(uint8_t cycle);
    bool SBC(uint8_t cycle);
    bool SEC(uint8_t cycle);
    bool SED(uint8_t cycle);
    bool SEI(uint8_t cycle);
    bool STA(uint8_t cycle);
    bool STX(uint8_t cycle);
    bool STY(uint8_t cycle);
    bool TAX(uint8_t cycle);
    bool TAY(uint8_t cycle);
    bool TSX(uint8_t cycle);
    bool TXA(uint8_t cycle);
    bool TXS(uint8_t cycle);
    bool TYA(uint8_t cycle);
    bool ILL(uint8_t cycle);

    std::vector<instruction> instructions;
};
