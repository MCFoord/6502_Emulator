#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include "bus.h"
#include "controlaction.h"

class Controller
{
public:
    Controller();
    ~Controller();
    void beginCpu();
    void loadProgram(std::string fileName);
    void unloadProgram();
    void setAction(ControlAction action);
    uint8_t readBus(uint16_t addr);
    void addBreakPoint();
    void removeBreakPoint();
    //need a graceful way to quit

private:
    std::thread m_cpuControlThread;
    Bus m_bus;
    CPU6502 m_cpu;
    bool m_stopCPUExecution = false;
    ControlAction m_chosenAction = ControlAction::NONE;
    std::mutex m_actionMutex;
    std::condition_variable m_actionCV;
    bool m_actionChosen = false;
    std::vector<int> m_breakpoints;

    void cpuControl();
    void cpuExecute();
    void cpuRun();
    void cpuReset();
};