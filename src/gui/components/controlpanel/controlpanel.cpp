#include <filesystem>
#include "controlpanel.h"
#include "imgui.h"

namespace fs = std::filesystem;

ControlPanel::ControlPanel(std::string id): m_id(id)
{
    
}

ControlPanel::~ControlPanel()
{

}

void ControlPanel::draw()
{
    fs::path p = fs::current_path();
 
    ImGui::TextUnformatted("This is for the controls");

    std::string path_to_dir = fs::current_path().string() + "/programs";
    for( const auto & entry : std::filesystem::directory_iterator( path_to_dir ) ){
        
    }

    if (ImGui::BeginCombo("##combo", "Select a program to load")) // The second parameter is the label previewed before opening the combo.
    {
        for ( const auto & entry : std::filesystem::directory_iterator( path_to_dir ) )
        {
            // bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(entry.path().string().c_str()))
                m_programFileName = entry.path().string();
            // if (is_selected)
            //     ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    if (ImGui::Button("Load Program", ImVec2(200, 100)))
    {
        m_fileLoaded = true;
    }

    ImGui::Button("Unload Program", ImVec2(200, 100));

    ImGui::Button("Execute", ImVec2(200, 100));
    ImGui::Button("Reset", ImVec2(200, 100));
    ImGui::Button("Run", ImVec2(200, 100));
    ImGui::Button("Set BreakPoint", ImVec2(200, 100));

    ImGui::End();
}