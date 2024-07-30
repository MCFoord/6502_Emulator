#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "window.h"
#include "cpu6502.h"
#include "cpuoption.h"
#include "bus.h"

void runCpu(CPU6502* cpu, std::mutex& mtx, std::condition_variable& cv, bool& ready, CpuOption* chosenOption)
{
    std::unique_lock<std::mutex> lock(mtx);
    bool shouldQuit = false;
    bool shouldStop = false;
    while (!shouldQuit)
    {
        cv.wait(lock, [&ready]{ return ready; });

        switch (*chosenOption)
        {
            case CpuOption::EXECUTE:
                std::cout << "EXECUTE" << '\n';
                cpu->execute();
                break;
            case CpuOption::RUN:
                std::cout << "RUN" << '\n';
                shouldStop = false;
                cpu->run(shouldStop);
                std::cout << "STOP" << '\n';
                break;
            case CpuOption::RESET:
                std::cout << "RESET" << '\n';
                cpu->reset();
                break;
            case CpuOption::QUIT:
                std::cout << "QUIT" << '\n';
                // shouldQuit = true;
                break;
        }

        ready = false;
    }
}

int main(int argc, char **argv) {
    std::mutex optionMtx;
    std::condition_variable optionSetCV;
    bool optionSet = false;
    CpuOption chosenOption = CpuOption::NONE;

    CPU6502 cpu = CPU6502();
    Bus bus = Bus();
    cpu.connectBus(&bus);


    std::thread cpuThread(runCpu, &cpu, std::ref(optionMtx), std::ref(optionSetCV), std::ref(optionSet), &chosenOption);


    Window window = Window(
        &bus, optionMtx, optionSetCV, optionSet, chosenOption
    );

    cpuThread.join();
    return 0;
}
