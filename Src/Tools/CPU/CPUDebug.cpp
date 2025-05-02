#include <iostream>
#include <memory>
#include <ncurses.h>
#include <CPU6502.h>
#include <Bus.h>
#include <fstream>
#include <sstream>

#define WINDOW_HEIGHT 50
#define WINDOW_WIDTH 50

std::string memToString(uint16_t start, uint16_t end)
{

    std::stringstream ss;
    int count = 0;
    ss << "    ";
    for (int i = 0; i < 16; ++i)
    {
        ss << std::setfill('0') << std::setw(2) << std::hex << i << " ";
    }

    ss << "\n";

    for (uint16_t i = start; i <= end; ++i)
    {
        if (count % 16 == 0)
        {
            ss << "\n" << std::setfill('0') << std::setw(2) << std::hex << count / 16 << "  ";
        }
        ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(ram[i]) << " ";
        ++count;
    }

    return ss.str();
}

std::string CPU6502::registerToString()
{
    std::stringstream ss;
    ss << "A: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(a) << ", "
       << "X: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(x) << ", "
       << "Y: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(y) << ", "
       << "SP: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(sp) << ", "
       << "PC: " << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(pc);
      
    return ss.str();
}

std::string CPU6502::instructionInfoToString()
{
    std::stringstream ss;

    ss << "PC value: (" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(read(pc)) << ") "
       << ", Next Instruction: " << currentInstruction.instructionName << ", Adressing Mode: " << currentInstruction.addressingModeName << "\n"
       << "Previous operation: {address: " << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(currentAddress)
       << ", Value: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(currentValue) << "}\n";

    return ss.str();
}

std::string CPU6502::statusToString()
{
    std::stringstream ss;
    ss << "C: " << getFlag(CPU6502::C) << ", "
       << "Z: " << getFlag(CPU6502::Z) << ", "
       << "I: " << getFlag(CPU6502::I) << ", "
       << "D: " << getFlag(CPU6502::D) << ", "
       << "B: " << getFlag(CPU6502::B) << ", "
       << "U: " << getFlag(CPU6502::U) << ", "
       << "V: " << getFlag(CPU6502::V) << ", "
       << "N: " << getFlag(CPU6502::N);

    return ss.str();
}

int main(int argc, char **argv)
{
    std::ofstream debugOutput;

    switch (argc)
    {
    case 1:
        std::cout << "[ERROR] binary file must be provided";
        return EXIT_FAILURE;
        break;

    case 2:
        break;

    case 3:
        debugOutput.open(argv[2]);
        if (!debugOutput.is_open())
        {
            std::cout << "[ERROR] output file could not be opened";
            return EXIT_FAILURE;
        }
        break;
    
    default:
        std::cout << "[ERROR] too many arguments provided";
        return EXIT_FAILURE;
        break;
    }

    std::shared_ptr<CPU6502> cpu = std::make_shared<CPU6502>();
    std::shared_ptr<Bus> bus1 = std::make_shared<Bus>();


    cpu->connectBus(bus1);
    bus1->loadProgram(argv[1]);
    cpu->reset();


    WINDOW* win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);
    initscr();
    noecho();
    curs_set(0);

    bool quit = false;

    int instructionCount = 0;
    while (!quit)
    {
        erase();
        addstr("---------------------- 6502 debug ----------------------\n\n");
        addstr("   options:\n");
        addstr("       - e to execute next instruction\n");
        addstr("       - a to run until illegal operation is encountered\n");
        addstr("       - r to reset\n");
        addstr("       - q to quit\n\n");
        addstr("--------------------------------------------------------\n\n\n");
        refresh();

        cpu->fetch();
        addstr("instruction Count: ");
        addstr(std::to_string(instructionCount).c_str());
        addstr("\n");
        addstr("Registers:\n\n");
        addstr(cpu->registerToString().c_str());
        addstr("\n");
        addstr(cpu->instructionInfoToString().c_str());
        addstr("\n\n");
        refresh();

        addstr("Status:\n\n");
        addstr(cpu->statusToString().c_str());
        addstr("\n\n");
        refresh();

        addstr("Zero Page:\n\n");
        addstr(bus1->memToString(0x0000, 0x00FF).c_str());
        addstr("\n\n");
        refresh();

        addstr("Stack:\n\n");
        addstr(bus1->memToString(0x0100, 0x01FF).c_str());
        addstr("\n\n");

        addstr("Program Data:\n\n");
        addstr(bus1->memToString(0x0400, 0x04FF).c_str());
        addstr("\n\n");

        refresh();

        int ch = getch();
        int count = 0;
        uint16_t currentPC = 0x00;
        int pcRepeatCount = 0;
        bool success = false;

        switch (ch)
        {
        case 'e':
            cpu->execute(debugOutput);
            instructionCount++;
            break;
            
        case 'q':
            quit = true;
            break;

        case 'a':

            while (cpu->currentInstruction.instructionName != "ILL" && pcRepeatCount < 3 && !success)
            {

                // cpu->execute(debugOutput);
                cpu->execute();
                if (cpu->pc == currentPC)
                {
                    pcRepeatCount++;
                }
                else if (cpu->pc == 0x3469 || cpu->pc == 0x346c)
                {
                    success = true;
                }
                else
                {
                    currentPC = cpu->pc;
                }
                instructionCount++;
            }

            cpu->printOperation(cpu->pc, debugOutput);
            break;

        case 'b':
            
            while (count < 40880)
            {
                erase();
                addstr(std::to_string(count).c_str());
                addstr(" instructions run successfully");
                refresh();
                cpu->execute(debugOutput);
                // cpu->execute();
                if (cpu->pc == currentPC)
                {
                    pcRepeatCount++;
                }
                else
                {
                    currentPC = cpu->pc;
                }
                ++count;
            }

            cpu->printOperation(cpu->pc, debugOutput);
            break;

        case 'r':
            bus1->loadProgram(argv[1]);
            cpu->reset();
            instructionCount = 0;
            break;
        
        default:
            break;
        }
    }

    endwin();
    return 0;
}