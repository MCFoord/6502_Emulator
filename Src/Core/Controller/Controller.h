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

    uint64_t CPUFullAddressSpaceSize() { return m_nes->CPUFullAddressSpaceSize(); }
    uint64_t CPURAMSize() { return m_nes->CPURAMSize(); }
    uint64_t cartridgePRGROMSize() { return m_nes->cartridgePRGROMSize(); }
    uint64_t cartridgePRGRAMSize() { return m_nes->cartridgePRGRAMSize(); }
    uint64_t cartridgeCHRRAMSize() { return m_nes->cartridgeCHRRAMSize(); }

    uint8_t CPURead(uint16_t addr) { return m_nes-> CPURead(addr); }
    uint8_t CPURAMRead(uint16_t addr) { return m_nes->CPURAMRead(addr); }
    uint8_t cartridgePRGROMRead(uint16_t addr) { return m_nes->cartridgePRGROMRead(addr); }
    uint8_t cartridgePRGRAMRead(uint16_t addr) { return m_nes->cartridgePRGRAMRead(addr); }
    uint8_t cartridgeCHRRAMRead(uint16_t addr) { return m_nes->cartridgeCHRRAMRead(addr); }

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