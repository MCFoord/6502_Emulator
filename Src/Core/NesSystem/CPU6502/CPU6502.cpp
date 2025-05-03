#include <memory>
#include "CPU6502.h"

#define ILLEGAL(opcode) {opcode, "ILL", "implicit", &CPU6502::implicit, &CPU6502::ILL, 2}

CPU6502::CPU6502()
{
    instructions = {
        {0x00, "BRK", "implicit", &CPU6502::implicit, &CPU6502::BRK, 7},
        {0x01, "ORA", "indirectX", &CPU6502::indirectX, &CPU6502::ORA, 6},
        ILLEGAL(0x02),
        ILLEGAL(0x03),
        ILLEGAL(0x04),
        {0x05, "ORA", "zeroPage", &CPU6502::zeroPage, &CPU6502::ORA, 3},
        {0x06, "ASL", "zeroPage", &CPU6502::zeroPage, &CPU6502::ASL, 5},
        ILLEGAL(0x07),
        {0x08, "PHP", "implicit", &CPU6502::implicit, &CPU6502::PHP, 3},
        {0x09, "ORA", "immediate", &CPU6502::immediate, &CPU6502::ORA, 2},
        {0x0A, "ASL", "accumulator", &CPU6502::accumulator, &CPU6502::ASL, 2},
        ILLEGAL(0x0B),
        ILLEGAL(0x0C),
        {0x0D, "ORA", "absolute", &CPU6502::absolute, &CPU6502::ORA, 4},
        {0x0E, "ASL", "absolute", &CPU6502::absolute, &CPU6502::ASL, 6},
        ILLEGAL(0x0F),

        {0x10, "BPL", "relative", &CPU6502::relative, &CPU6502::BPL, 2},
        {0x11, "ORA", "indirectY", &CPU6502::indirectY, &CPU6502::ORA, 5},
        ILLEGAL(0x12),
        ILLEGAL(0x13),
        ILLEGAL(0x14),
        {0x15, "ORA", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::ORA, 4},
        {0x16, "ASL", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::ASL, 6},
        ILLEGAL(0x17),
        {0x18, "CLC", "implicit", &CPU6502::implicit, &CPU6502::CLC, 2},
        {0x19, "ORA", "absoluteY", &CPU6502::absoluteY, &CPU6502::ORA, 4},
        ILLEGAL(0x1A),
        ILLEGAL(0x1B), 
        ILLEGAL(0x1C),
        {0x1D, "ORA", "absoluteX", &CPU6502::absoluteX, &CPU6502::ORA, 4},
        {0x1E, "ASL", "absoluteX", &CPU6502::absoluteX, &CPU6502::ASL, 7},
        ILLEGAL(0x1F),

        {0x20, "JSR", "absolute", &CPU6502::absolute, &CPU6502::JSR, 6},
        {0x21, "AND", "indirectX", &CPU6502::indirectX, &CPU6502::AND, 6},
        ILLEGAL(0x22),
        ILLEGAL(0x23),
        {0x24, "BIT", "zeroPage", &CPU6502::zeroPage, &CPU6502::BIT, 3},
        {0x25, "AND", "zeroPage", &CPU6502::zeroPage, &CPU6502::AND, 3},
        {0x26, "ROL", "zeroPage", &CPU6502::zeroPage, &CPU6502::ROL, 5},
        ILLEGAL(0x27),
        {0x28, "PLP", "implicit", &CPU6502::implicit, &CPU6502::PLP, 4},
        {0x29, "AND", "immediate", &CPU6502::immediate, &CPU6502::AND, 2},
        {0x2A, "ROL", "accumulator", &CPU6502::accumulator, &CPU6502::ROL, 2},
        ILLEGAL(0x2B),
        {0x2C, "BIT", "absolute", &CPU6502::absolute, &CPU6502::BIT, 4},
        {0x2D, "AND", "absolute", &CPU6502::absolute, &CPU6502::AND, 4},
        {0x2E, "ROL", "absolute", &CPU6502::absolute, &CPU6502::ROL, 6},
        ILLEGAL(0x2F),

        {0x30, "BMI", "relative", &CPU6502::relative, &CPU6502::BMI, 2},
        {0x31, "AND", "indirectY", &CPU6502::indirectY, &CPU6502::AND, 5},
        ILLEGAL(0x32),
        ILLEGAL(0x33),
        ILLEGAL(0x34),
        {0x35, "AND", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::AND, 4},
        {0x36, "ROL", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::ROL, 6},
        ILLEGAL(0x37),
        {0x38, "SEC", "implicit", &CPU6502::implicit, &CPU6502::SEC, 2},
        {0x39, "AND", "absoluteY", &CPU6502::absoluteY, &CPU6502::AND, 4},
        ILLEGAL(0x3A),
        ILLEGAL(0x3B),
        ILLEGAL(0x3C),
        {0x3D, "AND", "absoluteX", &CPU6502::absoluteX, &CPU6502::AND, 4},
        {0x3E, "ROL", "absoluteX", &CPU6502::absoluteX, &CPU6502::ROL, 7},
        ILLEGAL(0x3F),

        {0x40, "RTI", "implicit", &CPU6502::implicit, &CPU6502::RTI, 6},
        {0x41, "EOR", "indirectX", &CPU6502::indirectX, &CPU6502::EOR, 6},
        ILLEGAL(0x42),
        ILLEGAL(0x43),
        ILLEGAL(0x44),
        {0x45, "EOR", "zeroPage", &CPU6502::zeroPage, &CPU6502::EOR, 3},
        {0x46, "LSR", "zeroPage", &CPU6502::zeroPage, &CPU6502::LSR, 5},
        ILLEGAL(0x47),
        {0x48, "PHA", "implicit", &CPU6502::implicit, &CPU6502::PHA, 3},
        {0x49, "EOR", "immediate", &CPU6502::immediate, &CPU6502::EOR, 2},
        {0x4A, "LSR", "accumulator", &CPU6502::accumulator, &CPU6502::LSR, 2},
        ILLEGAL(0x4B),
        {0x4C, "JMP", "absolute", &CPU6502::absolute, &CPU6502::JMP, 3},
        {0x4D, "EOR", "absolute", &CPU6502::absolute, &CPU6502::EOR, 4},
        {0x4E, "LSR", "absolute", &CPU6502::absolute, &CPU6502::LSR, 6},
        ILLEGAL(0x4F),

        {0x50, "BVC", "relative", &CPU6502::relative, &CPU6502::BVC, 2},
        {0x51, "EOR", "indirectY", &CPU6502::indirectY, &CPU6502::EOR, 5},
        ILLEGAL(0x52),
        ILLEGAL(0x53),
        ILLEGAL(0x54),
        {0x55, "EOR", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::EOR, 4},
        {0x56, "LSR", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::LSR, 6},
        ILLEGAL(0x57),
        {0x58, "CLI", "implicit", &CPU6502::implicit, &CPU6502::CLI, 2},
        {0x59, "EOR", "absoluteY", &CPU6502::absoluteY, &CPU6502::EOR, 4},
        ILLEGAL(0x5A),
        ILLEGAL(0x5B),
        ILLEGAL(0x5C),
        {0x5D, "EOR", "absoluteX", &CPU6502::absoluteX, &CPU6502::EOR, 4},
        {0x5E, "LSR", "absoluteX", &CPU6502::absoluteX, &CPU6502::LSR, 7},
        ILLEGAL(0x5F),

        {0x60, "RTS", "implicit", &CPU6502::implicit, &CPU6502::RTS, 6},
        {0x61, "ADC", "indirectX", &CPU6502::indirectX, &CPU6502::ADC, 6},
        ILLEGAL(0x62),
        ILLEGAL(0x63),
        ILLEGAL(0x64),
        {0x65, "ADC", "zeroPage", &CPU6502::zeroPage, &CPU6502::ADC, 3},
        {0x66, "ROR", "zeroPage", &CPU6502::zeroPage, &CPU6502::ROR, 5},
        ILLEGAL(0x67),
        {0x68, "PLA", "implicit", &CPU6502::implicit, &CPU6502::PLA, 4},
        {0x69, "ADC", "immediate", &CPU6502::immediate, &CPU6502::ADC, 4},
        {0x6A, "ROR", "accumulator", &CPU6502::accumulator, &CPU6502::ROR, 2},
        ILLEGAL(0x6B),
        {0x6C, "JMP", "indirect", &CPU6502::indirect, &CPU6502::JMP, 5},
        {0x6D, "ADC", "absolute", &CPU6502::absolute, &CPU6502::ADC, 4},
        {0x6E, "ROR", "absolute", &CPU6502::absolute, &CPU6502::ROR, 6},
        ILLEGAL(0x6F),

        {0x70, "BVS", "relative", &CPU6502::relative, &CPU6502::BVS, 2},
        {0x71, "ADC", "indirectY", &CPU6502::indirectY, &CPU6502::ADC, 5},
        ILLEGAL(0x72),
        ILLEGAL(0x73),
        ILLEGAL(0x74),
        {0x75, "ADC", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::ADC, 4},
        {0x76, "ROR", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::ROR, 6},
        ILLEGAL(0x77),
        {0x78, "SEI", "implicit", &CPU6502::implicit, &CPU6502::SEI, 2},
        {0x79, "ADC", "absoluteY", &CPU6502::absoluteY, &CPU6502::ADC, },
        ILLEGAL(0x7A),
        ILLEGAL(0x7B),
        ILLEGAL(0x7C),
        {0x7D, "ADC", "absoluteX", &CPU6502::absoluteX, &CPU6502::ADC, 4},
        {0x7E, "ROR", "absoluteX", &CPU6502::absoluteX, &CPU6502::ROR, 7},
        ILLEGAL(0x7F),

        ILLEGAL(0x80),
        {0x81, "STA", "indirectX", &CPU6502::indirectX, &CPU6502::STA, 6},
        ILLEGAL(0x82),
        ILLEGAL(0x83),
        {0x84, "STY", "zeroPage", &CPU6502::zeroPage, &CPU6502::STY, 3},
        {0x85, "STA", "zeroPage", &CPU6502::zeroPage, &CPU6502::STA, 3},
        {0x86, "STX", "zeroPage", &CPU6502::zeroPage, &CPU6502::STX, 3},
        ILLEGAL(0x87),
        {0x88, "DEY", "implicit", &CPU6502::implicit, &CPU6502::DEY, 2},
        ILLEGAL(0x89),
        {0x8A, "TXA", "implicit", &CPU6502::implicit, &CPU6502::TXA, 2},
        ILLEGAL(0x8B),
        {0x8C, "STY", "absolute", &CPU6502::absolute, &CPU6502::STY, 4},
        {0x8D, "STA", "absolute", &CPU6502::absolute, &CPU6502::STA, 4},
        {0x8E, "STX", "absolute", &CPU6502::absolute, &CPU6502::STX, 4},
        ILLEGAL(0x8F),

        {0x90, "BCC", "relative", &CPU6502::relative, &CPU6502::BCC, 2},
        {0x91, "STA", "indirectY", &CPU6502::indirectY, &CPU6502::STA, 6},
        ILLEGAL(0x92),
        ILLEGAL(0x93),
        {0x94, "STY", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::STY, 4},
        {0x95, "STA", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::STA, 4},
        {0x96, "STX", "zeroPageY", &CPU6502::zeroPageY, &CPU6502::STX, 4},
        ILLEGAL(0x97),
        {0x98, "TYA", "implicit", &CPU6502::implicit, &CPU6502::TYA, 2},
        {0x99, "STA", "absoluteY", &CPU6502::absoluteY, &CPU6502::STA, 5},
        {0x9A, "TXS", "implicit", &CPU6502::implicit, &CPU6502::TXS, 2},
        ILLEGAL(0x9B),
        ILLEGAL(0x9C),
        {0x9D, "STA", "absoluteX", &CPU6502::absoluteX, &CPU6502::STA, 5},
        ILLEGAL(0x9E),
        ILLEGAL(0x9F),

        {0xA0, "LDY", "immediate", &CPU6502::immediate, &CPU6502::LDY, 2},
        {0xA1, "LDA", "indirectX", &CPU6502::indirectX, &CPU6502::LDA, 6},
        {0xA2, "LDX", "immediate", &CPU6502::immediate, &CPU6502::LDX, 2},
        ILLEGAL(0xA3),
        {0xA4, "LDY", "zeroPage", &CPU6502::zeroPage, &CPU6502::LDY, 4},
        {0xA5, "LDA", "zeroPage", &CPU6502::zeroPage, &CPU6502::LDA, 4},
        {0xA6, "LDX", "zeroPage", &CPU6502::zeroPage, &CPU6502::LDX, 4},
        ILLEGAL(0xA7),
        {0xA8, "TAY", "implicit", &CPU6502::implicit, &CPU6502::TAY, 2},
        {0xA9, "LDA", "immediate", &CPU6502::immediate, &CPU6502::LDA, 2},
        {0xAA, "TAX", "implicit", &CPU6502::implicit, &CPU6502::TAX, 2},
        ILLEGAL(0xAB),
        {0xAC, "LDY", "absolute", &CPU6502::absolute, &CPU6502::LDY, 4},
        {0xAD, "LDA", "absolute", &CPU6502::absolute, &CPU6502::LDA, 4},
        {0xAE, "LDX", "absolute", &CPU6502::absolute, &CPU6502::LDX, 4},
        ILLEGAL(0xAF),

        {0xB0, "BCS", "relative", &CPU6502::relative, &CPU6502::BCS, 2},
        {0xB1, "LDA", "indirectY", &CPU6502::indirectY, &CPU6502::LDA, 5},
        ILLEGAL(0xB2),
        ILLEGAL(0xB3),
        {0xB4, "LDY", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::LDY, 4},
        {0xB5, "LDA", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::LDA, 4},
        {0xB6, "LDX", "zeroPageY", &CPU6502::zeroPageY, &CPU6502::LDX, 4},
        ILLEGAL(0xB7),
        {0xB8, "CLV", "implicit", &CPU6502::implicit, &CPU6502::CLV, 2},
        {0xB9, "LDA", "absoluteY", &CPU6502::absoluteY, &CPU6502::LDA, 4},
        {0xBA, "TSX", "implicit", &CPU6502::implicit, &CPU6502::TSX, 2},
        ILLEGAL(0xBB),
        {0xBC, "LDY", "absoluteX", &CPU6502::absoluteX, &CPU6502::LDY, 4},
        {0xBD, "LDA", "absoluteX", &CPU6502::absoluteX, &CPU6502::LDA, 4},
        {0xBE, "LDX", "absoluteY", &CPU6502::absoluteY, &CPU6502::LDX, 4},
        ILLEGAL(0xBF),

        {0xC0, "CPY", "immediate", &CPU6502::immediate, &CPU6502::CPY, 2},
        {0xC1, "CMP", "indirectX", &CPU6502::indirectX, &CPU6502::CMP, 6},
        ILLEGAL(0xC2),
        ILLEGAL(0xC3),
        {0xC4, "CPY", "zeroPage", &CPU6502::zeroPage, &CPU6502::CPY, 3},
        {0xC5, "CMP", "zeroPage", &CPU6502::zeroPage, &CPU6502::CMP, 3},
        {0xC6, "DEC", "zeroPage", &CPU6502::zeroPage, &CPU6502::DEC, 5},
        ILLEGAL(0xC7),
        {0xC8, "INY", "implicit", &CPU6502::implicit, &CPU6502::INY, 2},
        {0xC9, "CMP", "immediate", &CPU6502::immediate, &CPU6502::CMP, 2},
        {0xCA, "DEX", "implicit", &CPU6502::implicit, &CPU6502::DEX, 2},
        ILLEGAL(0xCB),
        {0xCC, "CPY", "absolute", &CPU6502::absolute, &CPU6502::CPY, 4},
        {0xCD, "CMP", "absolute", &CPU6502::absolute, &CPU6502::CMP, 4},
        {0xCE, "DEC", "absolute", &CPU6502::absolute, &CPU6502::DEC, 6},
        ILLEGAL(0xCF),

        {0xD0, "BNE", "relative", &CPU6502::relative, &CPU6502::BNE, 2},
        {0xD1, "CMP", "indirectY", &CPU6502::indirectY, &CPU6502::CMP, 5},
        ILLEGAL(0xD2),
        ILLEGAL(0xD3),
        ILLEGAL(0xD4),
        {0xD5, "CMP", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::CMP, 4},
        {0xD6, "DEC", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::DEC, 6},
        ILLEGAL(0xD7),
        {0xD8, "CLD", "implicit", &CPU6502::implicit, &CPU6502::CLD, 2 },
        {0xD9, "CMP", "absoluteY", &CPU6502::absoluteY, &CPU6502::CMP, 4},
        ILLEGAL(0xDA),
        ILLEGAL(0xDB),
        ILLEGAL(0xDC),
        {0xDD, "CMP", "absoluteX", &CPU6502::absoluteX, &CPU6502::CMP, 4},
        {0xDE, "DEC", "absoluteX", &CPU6502::absoluteX, &CPU6502::DEC, 7},
        ILLEGAL(0xDF),

        {0xE0, "CPX", "immediate", &CPU6502::immediate, &CPU6502::CPX, 2},
        {0xE1, "SBC", "indirectX", &CPU6502::indirectX, &CPU6502::SBC, 6},
        ILLEGAL(0xE2),
        ILLEGAL(0xE3),
        {0xE4, "CPX", "zeroPage", &CPU6502::zeroPage, &CPU6502::CPX, 3},
        {0xE5, "SBC", "zeroPage", &CPU6502::zeroPage, &CPU6502::SBC, 3},
        {0xE6, "INC", "zeroPage", &CPU6502::zeroPage, &CPU6502::INC, 5},
        ILLEGAL(0xE7),
        {0xE8, "INX", "implicit", &CPU6502::implicit, &CPU6502::INX, 2},
        {0xE9, "SBC", "immediate", &CPU6502::immediate, &CPU6502::SBC, 2},
        {0xEA, "NOP", "implicit", &CPU6502::implicit, &CPU6502::NOP, 2},
        ILLEGAL(0xEB),
        {0xEC, "CPX", "absolute", &CPU6502::absolute, &CPU6502::CPX, 4},
        {0xED, "SBC", "absolute", &CPU6502::absolute, &CPU6502::SBC, 4},
        {0xEE, "INC", "absolute", &CPU6502::absolute, &CPU6502::INC, 6},
        ILLEGAL(0xEF),

        {0xF0, "BEQ", "relative", &CPU6502::relative, &CPU6502::BEQ, 2},
        {0xF1, "SBC", "indirectY", &CPU6502::indirectY, &CPU6502::SBC, 5},
        ILLEGAL(0xF2),
        ILLEGAL(0xF3),
        ILLEGAL(0xF4),
        {0xF5, "SBC", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::SBC, 4},
        {0xF6, "INC", "zeroPageX", &CPU6502::zeroPageX, &CPU6502::INC, 6},
        ILLEGAL(0xF7),
        {0xF8, "SED", "implicit", &CPU6502::implicit, &CPU6502::SED, 2},
        {0xF9, "SBC", "absoluteY", &CPU6502::absoluteY, &CPU6502::SBC, 4},
        ILLEGAL(0xFA),
        ILLEGAL(0xFB),
        ILLEGAL(0xFC),
        {0xFD, "SBC", "absoluteX", &CPU6502::absoluteX, &CPU6502::SBC, 4},
        {0xFE, "INC", "absoluteX", &CPU6502::absoluteX, &CPU6502::INC, 7},
        ILLEGAL(0xFF)
    };
}

CPU6502::~CPU6502()
{
    
}
    
void CPU6502::tick()
{
    if (m_extraCycle) //only for the addressing page boundaries - find a better way later
        m_extraCycle = false;
    else if (m_inResetState)
    {
        m_inResetState = false;
        fetch();
    }
    else if ((this->*m_currentInstruction.operation)(m_instructionCycleCount))
    {
        m_instructionCycleCount = 0;
        fetch();
    }

    m_instructionCycleCount++;
}

void CPU6502::reset()
{
    PC = 0xFFFC;
    A = 0x00;
    X = 0x00;
    Y = 0x00;
    SP = 0xFD;
    STATUS = 0x00;
    setFlag(CPUFLAGS::I, true);

    m_currentAddress = 0x0000;
    m_currentValue = 0x00;
    m_currentInstruction = {};
    m_inResetState = true;
    m_instructionCycleCount = 0;
}

void CPU6502::fetch()
{
    m_currentInstruction = instructions[read(PC++)];
}

uint8_t CPU6502::read(uint16_t addr)
{
    return m_bus->read(addr);
}

void CPU6502::write(uint16_t addr, uint8_t value)
{
    m_bus->write(addr, value);
}

void CPU6502::push(uint8_t value)
{
    write(0x0100 + SP, value);
    SP--;
}

uint8_t CPU6502::pop()
{
    SP++;
    return read(0x0100 + SP);
}

bool CPU6502::getFlag(CPUFLAGS flag)
{
    return flag & STATUS;
}

void CPU6502::setFlag(CPUFLAGS flag, bool set)
{
    if (set)
        STATUS |= flag;
    else
        STATUS &= ~(flag);
}

// addressing
bool CPU6502::implicit(uint8_t cycle)
{
    switch (cycle)
    {
    case 2:
        return false;
    default:
        return true;
    }
}

bool CPU6502::immediate(uint8_t cycle)
{
    switch (cycle)
    {
    case 2:
        m_currentValue = read(PC++);
        m_currentAddress = PC;
        return false;
    default:
        return true;
    }
}

bool CPU6502::accumulator(uint8_t cycle)
{
    switch (cycle)
    {
    case 2:
        m_currentValue = A;
        return false;
    default:
        return true;
    }
}

bool CPU6502::relative(uint8_t cycle)
{
    switch (cycle)
    {
    case 2:
    {
        uint16_t offset = read(PC++);

        if (offset & 0x80)
            offset |= 0xFF00;

        m_currentValue = offset;
        m_currentAddress = PC + offset;
        return false;
    }
    default:
        return true;
    }
}

//look up the page boundary bug for JMP opcode
bool CPU6502::indirect(uint8_t cycle)
{
    uint16_t pointerLow = read(PC++);
    uint8_t pointerHigh = read(PC);

    m_currentAddress = (pointerHigh << 8) | pointerLow; //lowbyte pointer

    uint16_t lowByte = read(m_currentAddress);
    uint8_t highByte = read(m_currentAddress + 1);

    if (pointerLow == 0xFF)
        //unsure if this is actually correct, but i'm tired
        highByte = read(((m_currentAddress & 0xFF00) << 8) | pointerLow);

    m_currentAddress = (highByte << 8) | lowByte;
    m_currentValue = read(m_currentAddress);
}

bool CPU6502::indirectX(uint8_t cycle)
{
    uint16_t lowByte = (read(PC++) + X) & 0x00FF;
    uint8_t highByte = (lowByte + 1) & 0xFF;

    m_currentAddress = (read(highByte) << 8) | read(lowByte);
    m_currentValue = read(m_currentAddress);
}

bool CPU6502::indirectY(uint8_t cycle)
{
    uint16_t lowByte = read(PC++);
    uint8_t highByte = (lowByte + 1) & 0xFF;

    m_currentAddress = ((read(highByte) << 8) | read(lowByte)) + Y;
    
    //FIX THIS to match the change above
    if ((m_currentAddress & 0xFF00) != highByte)
    {
        cycles++;
    }

    m_currentValue = read(m_currentAddress);
}

bool CPU6502::absolute(uint8_t cycle)
{
    uint16_t lowByte = 0;

    switch (cycle)
    {
    case 2:
        lowByte = read(PC++);
        return false;
    case 3:
        m_currentAddress = (read(PC++) << 8) | lowByte;
        return false;
    // case 4:
    //     m_currentValue = read(m_currentAddress); // this needs to go into each instruction
    //     return false;
    default:
        return true;
    }
} 

bool CPU6502::absoluteX(uint8_t cycle)
{
    uint16_t lowByte = read(PC++);
    uint8_t highByte = read(PC++);

	m_currentAddress = ((highByte << 8) | lowByte) + X;
	
    m_currentValue = read(m_currentAddress);
}

bool CPU6502::absoluteY(uint8_t cycle)
{
    uint16_t lowByte = read(PC++);
    uint8_t highByte = read(PC++);

    m_currentAddress = ((highByte << 8) | lowByte) + Y;

    if ((m_currentAddress & 0xFF00) != highByte)
    {
        cycles++;
    }

    m_currentValue = read(m_currentAddress);
}

/* check this later for any bugs to do with not actually
    assigning the value address to current address
*/
bool CPU6502::zeroPage(uint8_t cycle)
{
    m_currentAddress = read(PC++) & 0xFF;
    m_currentValue = read(m_currentAddress);
}   

bool CPU6502::zeroPageX(uint8_t cycle)
{
    m_currentAddress = (read(PC++) + X) & 0xFF;
    m_currentValue = read(m_currentAddress);
}

bool CPU6502::zeroPageY(uint8_t cycle)
{
    m_currentAddress = (read(PC++) + Y) & 0xFF;
    m_currentValue = read(m_currentAddress);
}

//interrupts
void CPU6502::NMI()
{
    setFlag(CPU6502::B, false);
    setFlag(CPU6502::U, false);

    PC++;
    push((PC >> 8) & 0xFF);
    push(PC & 0xFF);
    push(STATUS);

    setFlag(CPU6502::I, true);

    PC = (read(0xFFFB) << 8) | read(0xFFFA);
}

void CPU6502::IRQ()
{
    if (getFlag(CPU6502::I))
        return;
    
    setFlag(CPU6502::B, false);
    setFlag(CPU6502::U, false);

    PC++;
    push((PC >> 8) & 0xFF);
    push(PC & 0xFF);
    push(STATUS);

    setFlag(CPU6502::I, true);

    PC = (read(0xFFFF) << 8) | read(0xFFFE);
}

// inctructions
bool CPU6502::ADC(uint8_t cycle)
{
    uint16_t result = A + m_currentValue + getFlag(CPUFLAGS::C);

    if (getFlag(CPUFLAGS::D))
    {
        result = (A & 0x0F) + (m_currentValue & 0x0F) + getFlag(CPUFLAGS::C);
        if (result > 9) result += 0x06;

        result = (A & 0xF0) + (m_currentValue & 0xF0) + (result > 0x0F ? 0x10 : 0) + (result & 0x0F);
        if (result > 0x9F) result += 0x60;
    }

    setFlag(CPUFLAGS::Z, (result & 0xFF) == 0x00);
    setFlag(CPUFLAGS::C, (result > 0xFF));
    setFlag(CPUFLAGS::V, (A ^ result) & (m_currentValue ^ result) & 0x80);
    setFlag(CPUFLAGS::N, result & 0x80);

    A = result & 0xFF;
}

bool CPU6502::AND(uint8_t cycle)
{
    A &= m_currentValue;

    setFlag(CPUFLAGS::Z, A == 0x00);
    setFlag(CPUFLAGS::N, A & 0x80);

}

bool CPU6502::ASL(uint8_t cycle)
{
    /*
    need to worry about where the result is being writen to,
    need to differentiate between if it's the accumulator or A memory address
    */
    
    uint8_t result = (m_currentValue << 1);

    setFlag(CPUFLAGS::Z, result == 0x00);
    setFlag(CPUFLAGS::C, m_currentValue & 0x80);
    setFlag(CPUFLAGS::N, result & 0x80);


    if (m_currentInstruction.addressingMode == &CPU6502::accumulator)
    {
        A = result;
    }
    else
    {
        write(m_currentAddress, result);
    }
}

bool CPU6502::BCC(uint8_t cycle)
{
    if (!getFlag(CPUFLAGS::C))
    {
        cycles++;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BCS(uint8_t cycle)
{
    if (getFlag(CPUFLAGS::C))
    {
        cycles++;
        uint16_t rel = PC + m_currentValue;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BEQ(uint8_t cycle)
{
    if (getFlag(CPUFLAGS::Z))
    {
        cycles++;
        uint16_t rel = PC + m_currentValue;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BIT(uint8_t cycle)
{
    uint8_t result = A & m_currentValue;

    setFlag(CPUFLAGS::Z, !result);
    setFlag(CPUFLAGS::V, m_currentValue & 0x40);
    setFlag(CPUFLAGS::N, m_currentValue & 0x80);
}

bool CPU6502::BMI(uint8_t cycle)
{
    if (getFlag(CPUFLAGS::N))
    {
        cycles++;
        uint16_t rel = PC + m_currentValue;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BNE(uint8_t cycle)
{
    if (!getFlag(CPUFLAGS::Z))
    {
        cycles++;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BPL(uint8_t cycle)
{
    if (!getFlag(CPUFLAGS::N))
    {
        cycles++;
        uint16_t rel = PC + m_currentValue;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BRK(uint8_t cycle)
{
    setFlag(CPU6502::B, true);
    setFlag(CPU6502::U, true);

    PC++;
    push((PC >> 8) & 0xFF);
    push(PC & 0xFF);
    push(STATUS);

    setFlag(CPU6502::I, true);

    PC = (read(0xFFFF) << 8) | read(0xFFFE);
}

bool CPU6502::BVC(uint8_t cycle)
{
    if (!getFlag(CPUFLAGS::V))
    {
        cycles++;
        uint16_t rel = PC + m_currentValue;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::BVS(uint8_t cycle)
{
    if (getFlag(CPUFLAGS::V))
    {
        cycles++;
        uint16_t rel = PC + m_currentValue;

        if ((m_currentAddress & 0xFF00) != (PC & 0xFF00))
        {
            cycles++;
        }

        PC = m_currentAddress;
    }
}

bool CPU6502::CLC(uint8_t cycle)
{
    setFlag(CPU6502::C, false);
}

bool CPU6502::CLD(uint8_t cycle)
{
    setFlag(CPU6502::D, false);
}

bool CPU6502::CLI(uint8_t cycle)
{
    setFlag(CPU6502::I, false);
}

bool CPU6502::CLV(uint8_t cycle)
{
    setFlag(CPU6502::V, false);
}

bool CPU6502::CMP(uint8_t cycle)
{
    uint8_t result = A - m_currentValue;

    setFlag(CPU6502::C, (A >= m_currentValue));
    setFlag(CPU6502::Z, (A == m_currentValue));
    setFlag(CPU6502::N, (result & 0x80));
}

bool CPU6502::CPX(uint8_t cycle)
{
    uint8_t result = X - m_currentValue;

    setFlag(CPU6502::C, (X >= m_currentValue));
    setFlag(CPU6502::Z, (X == m_currentValue));
    setFlag(CPU6502::N, (result & 0x80));
}

bool CPU6502::CPY(uint8_t cycle)
{
    uint8_t result = Y - m_currentValue;

    setFlag(CPU6502::C, (Y >= m_currentValue));
    setFlag(CPU6502::Z, (Y == m_currentValue));
    setFlag(CPU6502::N, (result & 0x80));
}

bool CPU6502::DEC(uint8_t cycle)
{
    uint8_t result = m_currentValue - 1;

    write(m_currentAddress, result);
    setFlag(CPU6502::Z, (result == 0x00));
    setFlag(CPU6502::N, (result & 0x80));
}

bool CPU6502::DEX(uint8_t cycle)
{
    X--;

    setFlag(CPU6502::Z, (X == 0x00));
    setFlag(CPU6502::N, (X & 0x80));
}

bool CPU6502::DEY(uint8_t cycle)
{
    Y--;

    setFlag(CPU6502::Z, (Y == 0x00));
    setFlag(CPU6502::N, (Y & 0x80));
}

bool CPU6502::EOR(uint8_t cycle)
{
    A ^= m_currentValue;

    setFlag(CPU6502::Z, (A == 0x00));
    setFlag(CPU6502::N, (A & 0x80));
}

bool CPU6502::INC(uint8_t cycle)
{
    uint8_t result = m_currentValue + 1;

    write(m_currentAddress, result);
    setFlag(CPU6502::Z, (result == 0x00));
    setFlag(CPU6502::N, (result & 0x80));
}

bool CPU6502::INX(uint8_t cycle)
{
    X++;

    setFlag(CPU6502::Z, (X == 0x00));
    setFlag(CPU6502::N, (X & 0x80));
}

bool CPU6502::INY(uint8_t cycle)
{
    Y++;

    setFlag(CPU6502::Z, (Y == 0x00));
    setFlag(CPU6502::N, (Y & 0x80));
}

//go to indirect page boundary bug
bool CPU6502::JMP(uint8_t cycle)
{
    PC = m_currentAddress;
}

bool CPU6502::JSR(uint8_t cycle)
{
    PC--;
    push((PC >> 8) & 0xFF);
    push(PC & 0xFF);
    PC = m_currentAddress;
}

bool CPU6502::LDA(uint8_t cycle)
{
    A = m_currentValue;
    setFlag(CPU6502::Z, (A == 0x00));
    setFlag(CPU6502::N, (A & 0x80));
}

bool CPU6502::LDX(uint8_t cycle)
{
    X = m_currentValue;
    setFlag(CPU6502::Z, (X == 0x00));
    setFlag(CPU6502::N, (X & 0x80));
}

bool CPU6502::LDY(uint8_t cycle)
{
    Y = m_currentValue;
    setFlag(CPU6502::Z, (Y == 0x00));
    setFlag(CPU6502::N, (Y & 0x80));
}

bool CPU6502::LSR(uint8_t cycle)
{
    if (m_currentInstruction.addressingMode == &CPU6502::accumulator)
    {
        setFlag(CPU6502::C, (A & 0x01));
        A = (A >> 1);
        setFlag(CPU6502::Z, (A == 0x00));
        setFlag(CPU6502::N, (A & 0x80));
    }
    else
    {
        uint8_t result = (m_currentValue >> 1);

        setFlag(CPU6502::C, (m_currentValue & 0x01));
        setFlag(CPU6502::Z, (result == 0x00));
        setFlag(CPU6502::N, (result & 0x80));
        write(m_currentAddress, result);
    }
}

bool CPU6502::NOP(uint8_t cycle)
{

}

bool CPU6502::ORA(uint8_t cycle)
{
    A |= m_currentValue;

    setFlag(CPU6502::Z, (A == 0x00));
    setFlag(CPU6502::N, (A & 0x80));
}

bool CPU6502::PHA(uint8_t cycle)
{
    push(A);
}

bool CPU6502::PHP(uint8_t cycle)
{
    setFlag(CPU6502::B, true);
    setFlag(CPU6502::U, true);
    push(STATUS);
}

bool CPU6502::PLA(uint8_t cycle)
{
    A = pop();
    setFlag(CPU6502::Z, (A == 0x00));
    setFlag(CPU6502::N, (A & 0x80));
}

bool CPU6502::PLP(uint8_t cycle)
{
    STATUS = pop();
}

bool CPU6502::ROL(uint8_t cycle)
{
    
    if (m_currentInstruction.addressingMode == &CPU6502::accumulator)
    {
        uint8_t result = (A << 1) | getFlag(CPU6502::C);

        setFlag(CPU6502::C, (A & 0x80));
        setFlag(CPU6502::Z, (result == 0x00));
        setFlag(CPU6502::N, (result & 0x80));
        A = result;
    }
    else
    {
        uint8_t result = (m_currentValue << 1) | getFlag(CPU6502::C);

        setFlag(CPU6502::C, (m_currentValue & 0x80));
        setFlag(CPU6502::Z, (result == 0x00));
        setFlag(CPU6502::N, (result & 0x80));
        write(m_currentAddress, result);
    }
}

bool CPU6502::ROR(uint8_t cycle)
{
    if (m_currentInstruction.addressingMode == &CPU6502::accumulator)
    {
        uint8_t result = (A >> 1) | (getFlag(CPU6502::C) << 7);

        setFlag(CPU6502::C, (A & 0x01));
        setFlag(CPU6502::Z, (result == 0x00));
        setFlag(CPU6502::N, (result & 0x80));
        A = result;
    }
    else
    {
        uint8_t result = (m_currentValue >> 1) | (getFlag(CPU6502::C) << 7);

        setFlag(CPU6502::C, (m_currentValue & 0x01));
        setFlag(CPU6502::Z, (result == 0x00));
        setFlag(CPU6502::N, (result & 0x80));
        write(m_currentAddress, result);
    }
}

bool CPU6502::RTI(uint8_t cycle)
{
    STATUS = pop();
    uint8_t lowByte = pop();
    uint8_t highByte = pop();
    

    PC = (highByte << 8) | lowByte;
}

bool CPU6502::RTS(uint8_t cycle)
{
    uint16_t lowByte = pop();
    uint8_t highByte = pop();

    PC = (highByte << 8) | lowByte;
    PC++;
}

bool CPU6502::SBC(uint8_t cycle)
{
    uint16_t flipped = m_currentValue ^ 0xFF;
    uint16_t result = A + flipped + getFlag(CPUFLAGS::C);

    if (getFlag(CPUFLAGS::D))
    {
        result = (A & 0x0F) + (flipped & 0x0F) + getFlag(CPUFLAGS::C);
        if (result <= 0xF) result -= 0x06;

        result = (A & 0xF0) + (flipped & 0xF0) + (result > 0x0F ? 0x10 : 0) + (result & 0x0F);
        if (result <= 0xFF) result -= 0x60;
    }

    setFlag(CPUFLAGS::Z, (result & 0xFF) == 0x00);
    setFlag(CPUFLAGS::C, result & 0xFF00);
    setFlag(CPUFLAGS::V, ((A ^ result) & (flipped ^ result)) & 0x80);
    setFlag(CPUFLAGS::N, result & 0x80);

    A = result & 0xFF;
}

bool CPU6502::SEC(uint8_t cycle)
{
    setFlag(CPUFLAGS::C, true);
}

bool CPU6502::SED(uint8_t cycle)
{
    setFlag(CPUFLAGS::D, true);
}

bool CPU6502::SEI(uint8_t cycle)
{
    setFlag(CPUFLAGS::I, true);
}

bool CPU6502::STA(uint8_t cycle)
{
    write(m_currentAddress, A);
}

bool CPU6502::STX(uint8_t cycle)
{
    write(m_currentAddress, X);
}

bool CPU6502::STY(uint8_t cycle)
{
    write(m_currentAddress, Y);
}

bool CPU6502::TAX(uint8_t cycle)
{
    X = A;
    setFlag(CPU6502::Z, (X == 0x00));
    setFlag(CPU6502::N, (X & 0x80));
}

bool CPU6502::TAY(uint8_t cycle)
{
    Y = A;
    setFlag(CPU6502::Z, (Y == 0x00));
    setFlag(CPU6502::N, (Y & 0x80));
}

bool CPU6502::TSX(uint8_t cycle)
{
    X = SP;
    setFlag(CPU6502::Z, (X == 0x00));
    setFlag(CPU6502::N, (X & 0x80));
}

bool CPU6502::TXA(uint8_t cycle)
{
    A = X;
    setFlag(CPU6502::Z, (A == 0x00));
    setFlag(CPU6502::N, (A & 0x80));
}

bool CPU6502::TXS(uint8_t cycle) 
{
    SP = X;
}

bool CPU6502::TYA(uint8_t cycle)
{
    A = Y;
    setFlag(CPU6502::Z, (A == 0x00));
    setFlag(CPU6502::N, (A & 0x80));
}


bool CPU6502::ILL(uint8_t cycle)
{

}