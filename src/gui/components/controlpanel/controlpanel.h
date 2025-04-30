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
    const std::string m_kdefaultProgramText = "Select a program to load";
    //sizes
    std::string m_id;
    Window* m_parent;
    Controller& m_controller;
    std::filesystem::path m_programFilePath;
};