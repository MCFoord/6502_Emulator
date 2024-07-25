#pragma once

#include <string>
#include "component.h"
#include "bus.h"
#include "cpu6502.h"
#include "window.h"

class ControlPanel: public Component
{
public:
    ControlPanel(std::string id, CPU6502* cpu, Bus* bus,  Window* window);
    ~ControlPanel();
    void draw() override;
private:
    //sizes
    std::string m_id;
    bool m_fileLoaded = false;
    bool m_showFilePicker = false;
    std::string m_programFileName = "Select a program to load";

    Bus* m_bus;
    CPU6502* m_cpu;

    Window* m_window;
};