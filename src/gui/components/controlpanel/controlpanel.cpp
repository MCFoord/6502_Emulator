#include <filesystem>
#include "controlpanel.h"
#include "imgui.h"
#include "window.h"

ControlPanel::ControlPanel(std::string id, CPU6502* cpu, Bus* bus, Window* window):
m_id(id),
m_bus(bus),
m_cpu(cpu),
m_window(window)
{

}

ControlPanel::~ControlPanel()
{

}

void ControlPanel::draw()
{    
    ImGui::Begin(m_id.c_str());

    std::string programDir = std::filesystem::current_path().string() + "/programs";

    if (ImGui::BeginCombo("##combo", m_programFileName.c_str()))
    {
        for (const auto & entry : std::filesystem::directory_iterator(programDir))
        {
            if (ImGui::Selectable(entry.path().string().c_str()))
                m_programFileName = entry.path().string();
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (ImGui::Button("Load Program", ImVec2(200, 100)))
    {
        //load program
        m_bus->loadProgram(m_programFileName.c_str());
        m_fileLoaded = true;
    }

    if (ImGui::Button("Unload Program", ImVec2(200, 100)))
    {
        //set all ram to 0x00
        m_bus->clearmemory();
    }

    if (ImGui::Button("Add memory view", ImVec2(200, 100)))
    {
        m_window->createNewHexView();
    }

    if (ImGui::Button("Execute", ImVec2(200, 100)))
    {
        //step one instruction
        m_cpu->execute();
    }

    if (ImGui::Button("Reset", ImVec2(200, 100)))
    {
        //call cpu reset
        m_cpu->reset();
    }

    if (ImGui::Button("Run", ImVec2(200, 100)))
    {
        //run program until an illegal operation is encountered or program is finished
        m_cpu->run();
    }

    if (ImGui::Button("Set BreakPoint", ImVec2(200, 100)))
    {
        //set a breakpoint in the program
    }

    ImGui::End();
}
