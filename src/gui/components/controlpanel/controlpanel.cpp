#include <filesystem>
#include "controlpanel.h"
#include "imgui.h"
#include "window.h"

ControlPanel::ControlPanel(
    std::string id, Window* parent, Controller& controller
):
m_id(id),
m_parent(parent),
m_controller(controller)
{

}

ControlPanel::~ControlPanel()
{

}

void ControlPanel::draw()
{    
    ImGui::Begin(m_id.c_str());

    //change this to use the path object
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
        m_controller.setAction(ControlAction::RESET);
        m_controller.loadProgram(m_programFileName);
        //i think i'll need a better solution for this (technically potential for a race) but should be okay for now
    }

    if (ImGui::Button("Unload Program", ImVec2(200, 100)))
    {
        //set all ram to 0x00
        m_controller.setAction(ControlAction::RESET);
        m_controller.unloadProgram();
    }

    if (ImGui::Button("Add memory view", ImVec2(200, 100)))
    {
        m_parent->createNewHexView();
    }

    if (ImGui::Button("Execute", ImVec2(200, 100)))
    {
        //step one instruction
        m_controller.setAction(ControlAction::EXECUTE);
    }

    if (ImGui::Button("Reset", ImVec2(200, 100)))
    {
        //call cpu reset
        m_controller.setAction(ControlAction::RESET);
    }

    if(!m_controller.cpuIsRunning())
    {
        if (ImGui::Button("Run", ImVec2(200, 100)))
        {
            //run program until an illegal operation is encountered or program is finished
            m_controller.setAction(ControlAction::RUN);
        }
    }
    else
    {
        if (ImGui::Button("Stop", ImVec2(200, 100)))
        {
            m_controller.stopCpu();
        }
    }
    
    if (ImGui::Button("Quit", ImVec2(200, 100)))
    {
        m_controller.setAction(ControlAction::QUIT);
    }

    ImGui::End();
}
