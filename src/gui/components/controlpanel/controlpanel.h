#pragma once

#include <string>
#include "component.h"
#include "bus.h"
#include "cpu6502.h"
#include "window.h"

class ControlPanel: public Component
{
public:
    ControlPanel(
        std::string id, Bus* bus, std::mutex& mtx, std::condition_variable& cv,
        bool& optionSet, CpuOption& option, Window* window
    );
    ~ControlPanel();
    void draw() override;
private:
    //sizes
    std::mutex& m_cpuOptionLock;
    std::condition_variable& m_cpuOptionSetCV;
    CpuOption& m_chosenOption;
    bool& m_optionSet;
    std::string m_id;
    bool m_fileLoaded = false;
    bool m_showFilePicker = false;
    std::string m_programFileName = "Select a program to load";
    Bus* m_bus;
    Window* m_window;

    void setCpuOption(CpuOption chosenOption);
};