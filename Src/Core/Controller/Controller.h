#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include "ControlAction.h"
#include "NesSystem.h"

class Controller
{
public:
    Controller();
    ~Controller();
    void beginCpuThread();
    void endCpuThread();
    bool cpuIsRunning();
    void stopCpu();
    void loadProgram(std::filesystem::path path);
    void unloadProgram();
    void setAction(ControlAction action);
    void addBreakpoint(int addr);
    bool removeBreakpoint(int addr);
    bool isBreakpoint(int addr);
    uint8_t readBus(uint16_t addr);
    //need a graceful way to quit

private:
    std::thread m_cpuControlThread;
    std::shared_ptr<NESSystem> m_nes;
    bool m_stopCPUExecution = false;
    bool m_cpuIsRunning = false;
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