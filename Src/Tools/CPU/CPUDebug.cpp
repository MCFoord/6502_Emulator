#include <iostream>
#include <memory>
#include <ncurses.h>
#include <CPU6502.h>
#include <Bus.h>
#include <fstream>
#include <sstream>
#include <string>

#define WINDOW_HEIGHT 50
#define WINDOW_WIDTH 50

std::string memToString(std::shared_ptr<Bus> bus, uint16_t start, uint16_t end)
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
        ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(bus->read(i)) << " ";
        ++count;
    }

    return ss.str();
}

std::string registerToString(CPUState state)
{
    std::stringstream ss;
    ss << "A: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(state.A) << ", "
       << "X: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(state.X) << ", "
       << "Y: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(state.Y) << ", "
       << "SP: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(state.SP) << ", "
       << "PC: " << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(state.PC);
      
    return ss.str();
}

std::string instructionInfoToString(CPUState state)
{
    std::stringstream ss;

    ss << "PC value: (" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(state.opcode) << ") "
       << ", Next Instruction: " << state.instructionName << ", Adressing Mode: " << state.addressingModeName << "\n"
       << "Previous operation: {address: " << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(state.currentAddress)
       << ", Value: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(state.currentValue) << "}\n";

    return ss.str();
}

std::string statusToString(CPUState state)
{
    std::stringstream ss;
    ss << "C: " << state.C << ", "
       << "Z: " << state.Z << ", "
       << "I: " << state.I << ", "
       << "D: " << state.D << ", "
       << "B: " << state.B << ", "
       << "U: " << state.U << ", "
       << "V: " << state.V << ", "
       << "N: " << state.N;

    return ss.str();
}

void executeInstruction(std::shared_ptr<CPU6502> cpu)
{
    while (! cpu->tick()) {}
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
    std::shared_ptr<Bus> bus1 = std::make_shared<Bus>(64 * 1024);


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

        CPUState state = cpu->getCPUState();
        addstr("instruction Count: ");
        addstr(std::to_string(instructionCount).c_str());
        addstr("\n");
        addstr("instruction cycle: ");
        addstr(std::to_string(state.instructionCycle).c_str());
        addstr("\n");
        addstr("Registers:\n\n");
        addstr(registerToString(state).c_str());
        addstr("\n");
        addstr(instructionInfoToString(state).c_str());
        addstr("\n\n");
        refresh();

        addstr("Status:\n\n");
        addstr(statusToString(state).c_str());
        addstr("\n\n");
        refresh();

        addstr("Zero Page:\n\n");
        addstr(memToString(bus1, 0x0000, 0x00FF).c_str());
        addstr("\n\n");
        refresh();

        addstr("Stack:\n\n");
        addstr(memToString(bus1, 0x0100, 0x01FF).c_str());
        addstr("\n\n");

        addstr("Program Data:\n\n");
        addstr(memToString(bus1, 0x0400, 0x04FF).c_str());
        addstr("\n\n");

        refresh();

        int ch = getch();
        int count = 0;
        uint16_t currentPC = 0x00;
        bool PCRepeat = false;
        bool success = false;

        switch (ch)
        {
        case 't':
            cpu->tick();
            break;
        case 'e':
            executeInstruction(cpu);
            instructionCount++;
            break;
            
        case 'q':
            quit = true;
            break;

        case 'a':
        {
            //fix this up to use cpu state to test for the success or fail states
            CPUState currState = cpu->getCPUState();
            // while (cpu->currentInstruction.instructionName != "ILL" && pcRepeatCount < 3 && !success)
            while (currState.instructionName != "ILL" && !PCRepeat && !success)
            {
                executeInstruction(cpu);
                currState = cpu->getCPUState();

                if (currState.PC == currentPC)
                    PCRepeat = true;
                else if (currState.PC == 0x3469 || currState.PC == 0x346c)
                    success = true;


                currentPC = currState.PC;
                instructionCount++;
            }
            // cpu->printOperation(cpu->pc, debugOutput);
            break;
        }
        case 'b':
            
            while (count < 46615)
            {
                erase();
                addstr(std::to_string(count).c_str());
                addstr(" instructions run successfully");
                refresh();
                executeInstruction(cpu);
                // cpu->execute();
                if (state.PC == currentPC)
                {
                    // pcRepeatCount++;
                }
                else
                {
                    currentPC = state.PC;
                }
                ++count;
            }

            // cpu->printOperation(cpu->pc, debugOutput);
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