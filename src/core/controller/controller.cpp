#include <iostream>
#include "Controller.h"

Controller::Controller()
{
    m_bus = std::make_shared<Bus>();
    m_cpu = std::make_shared<CPU6502>();
    m_cpu->connectBus(m_bus);
    m_breakpoints = std::vector<int>();
    beginCpuThread();
}

Controller::~Controller()
{

}

void Controller::beginCpuThread()
{
    m_cpuControlThread = std::thread([this] { cpuControl(); });
}

void Controller::endCpuThread()
{
    if (cpuIsRunning()) { stopCpu(); }
    setAction(ControlAction::QUIT);
    if (m_cpuControlThread.joinable())
    {
        std::cout << "Waiting for thread to join\n";
        m_cpuControlThread.join();
        std::cout << "Thread Terminated\n";
    }
}

bool Controller::cpuIsRunning()
{
    return m_cpuIsRunning;
}

void Controller::stopCpu()
{
    m_stopCPUExecution = true;
    m_cpuIsRunning = false;
}

void Controller::loadProgram(std::string fileName)
{
    if (cpuIsRunning()) { stopCpu(); }

    m_bus->loadProgram(fileName.c_str());
}

void Controller::unloadProgram()
{
    if (cpuIsRunning()) { stopCpu(); }

    m_bus->clearmemory();
}

void Controller::setAction(ControlAction action)   
{
    std::lock_guard<std::mutex> lock(m_actionMutex);
    m_chosenAction = action;
    m_actionChosen = true;
    m_actionCV.notify_all();
}

void Controller::addBreakpoint(int addr)
{
    std::vector<int>::iterator it = std::lower_bound(
        m_breakpoints.begin(), m_breakpoints.end(), addr
    );
    m_breakpoints.insert(it, addr);
}

bool Controller::removeBreakpoint(int addr)
{
    std::vector<int>::iterator it = std::find(
        m_breakpoints.begin(), m_breakpoints.end(), addr
    );

    if (it != m_breakpoints.end())
    {
        m_breakpoints.erase(it);
        return true;
    }

    return false;
}

bool Controller::isBreakpoint(int addr)
{
    return std::binary_search(m_breakpoints.begin(), m_breakpoints.end(), addr);
}

uint8_t Controller::readBus(uint16_t addr)
{
    return m_bus->read(addr);
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
                shouldQuit = true;
                break;
            case ControlAction::NONE:
            default:
                break;
        }
        m_actionChosen = false;
    }
}

void Controller::cpuExecute()
{
    m_cpu->execute();
}

void Controller::cpuRun()
{
    m_stopCPUExecution = false;
    m_cpuIsRunning = true;
    m_cpu->run(m_stopCPUExecution, m_breakpoints);
}

//possible hanging issue
void Controller::cpuReset()
{
    if (cpuIsRunning()) { stopCpu(); }
    m_cpu->reset();
}
