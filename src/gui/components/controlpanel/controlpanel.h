#pragma once

#include <string>
#include "component.h"
#include "bus.h"
#include "cpu6502.h"
#include "window.h"
#include "controller.h"

class ControlPanel: public Component
{
public:
    ControlPanel(
        std::string id,  Window* parent, Controller& controller
    );
    ~ControlPanel();
    void draw() override;
private:
    //sizes
    std::string m_id;
    Window* m_parent;
    Controller& m_controller;
    std::string m_programFileName = "Select a program to load";
};