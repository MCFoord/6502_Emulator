#include <filesystem>
#include "controlpanel.h"
#include "imgui.h"
#include "window.h"
#include "cpuoption.h"

ControlPanel::ControlPanel(
    std::string id, Bus* bus, std::mutex& mtx, std::condition_variable& cv,
    bool& optionSet, CpuOption& option, Window* window
):
m_id(id),
m_bus(bus),
m_window(window),
m_cpuOptionLock(mtx),
m_cpuOptionSetCV(cv),
m_chosenOption(option),
m_optionSet(optionSet)
{

}

ControlPanel::~ControlPanel()
{

}

void ControlPanel::setCpuOption(CpuOption chosenOption)
{
    std::lock_guard<std::mutex> lock(m_cpuOptionLock);
    m_chosenOption = chosenOption;
    m_optionSet = true;
    
    m_cpuOptionSetCV.notify_all();
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
        m_bus->loadProgram(m_programFileName.c_str());
        m_fileLoaded = true;
        setCpuOption(CpuOption::RESET);
    }

    if (ImGui::Button("Unload Program", ImVec2(200, 100)))
    {
        //set all ram to 0x00
        m_bus->clearmemory();
        m_fileLoaded = false;
        setCpuOption(CpuOption::RESET);
    }

    if (ImGui::Button("Add memory view", ImVec2(200, 100)))
    {
        m_window->createNewHexView();
    }

    if (ImGui::Button("Execute", ImVec2(200, 100)))
    {
        //step one instruction
        setCpuOption(CpuOption::EXECUTE);
    }

    if (ImGui::Button("Reset", ImVec2(200, 100)))
    {
        //call cpu reset
        setCpuOption(CpuOption::RESET);
    }

    if (ImGui::Button("Run", ImVec2(200, 100)))
    {
        //run program until an illegal operation is encountered or program is finished
        setCpuOption(CpuOption::RUN);
    }

    if (ImGui::Button("Set BreakPoint", ImVec2(200, 100)))
    {
        //set a breakpoint in the program
    }

    if (ImGui::Button("Quit", ImVec2(200, 100)))
    {
        setCpuOption(CpuOption::QUIT);
    }

    ImGui::End();
}
