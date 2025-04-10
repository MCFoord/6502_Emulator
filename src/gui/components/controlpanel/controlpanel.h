#pragma once

#include <string>
#include "Component.h"
#include "Window.h"
#include "Controller.h"

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