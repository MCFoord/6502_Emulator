#include <iostream>
#include "controller.h"

Controller::Controller()
{
    m_bus = Bus();
    m_cpu = CPU6502();
    m_cpu.connectBus(&m_bus);
    m_breakpoints = std::vector<int>();
    beginCpu();
}

Controller::~Controller()
{

}

void Controller::beginCpu()
{
    m_cpuControlThread = std::thread([this] { cpuControl(); });
}

void Controller::cpuControl()
{
    std::unique_lock<std::mutex> lock(m_actionMutex);
    bool shouldQuit = false;
    while (!shouldQuit)
    {
        m_actionCV.wait(lock, [this]{ return m_actionChosen; });

        switch (m_chosenAction)
        {
            case ControlAction::EXECUTE:
                std::cout << "EXECUTE" << '\n';
                cpuExecute();
                break;
            case ControlAction::RUN:
                std::cout << "RUN" << '\n';
                cpuRun();
                std::cout << "STOP" << '\n';
                break;
            case ControlAction::RESET:
                std::cout << "RESET" << '\n';
                cpuReset();
                break;
            case ControlAction::QUIT:
                std::cout << "QUIT" << '\n';
                shouldQuit = true;
                break;
        }

        m_actionChosen = false;
    }
}

void Controller::setAction(ControlAction action)   
{
    std::lock_guard<std::mutex> lock(m_actionMutex);
    m_chosenAction = action;
    m_actionChosen = true;
    m_actionCV.notify_all();
}

void Controller::loadProgram(std::string fileName)
{
    m_bus.loadProgram(fileName.c_str());
}

void Controller::unloadProgram()
{
    m_bus.clearmemory();
}

uint8_t Controller::readBus(uint16_t addr)
{
    return m_bus.read(addr);
}

void Controller::cpuExecute()
{
    m_cpu.execute();
}

void Controller::cpuRun()
{
    m_cpu.run();
}

void Controller::cpuReset()
{
    m_cpu.reset();
}
