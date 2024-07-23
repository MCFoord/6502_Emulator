#include "controlpanel.h"
#include "imgui.h"

ControlPanel::ControlPanel(std::string id): m_id(id)
{
    
}

ControlPanel::~ControlPanel()
{

}

void ControlPanel::draw()
{
    ImGui::Begin(m_id.c_str());
 
    ImGui::TextUnformatted("This is for the controls");

    ImGui::End();
}