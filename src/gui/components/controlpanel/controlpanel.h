#pragma once

#include <string>
#include "component.h"

class ControlPanel: public Component
{
public:
    ControlPanel(std::string id);
    ~ControlPanel();
    void draw() override;
private:
    //sizes
    std::string m_id;
    bool m_fileLoaded = false;
    bool m_showFilePicker = false;
    std::string m_programFileName;
};