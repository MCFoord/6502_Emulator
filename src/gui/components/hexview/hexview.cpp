#include "hexview.h"
#include "imgui.h"

HexView::HexView(std::string id): m_id(id)
{
    
}

HexView::~HexView()
{

}

void HexView::draw()
{
    ImGui::Begin(m_id.c_str());
    for (int i = 0x0000; i <= 0xFFFF; i++)
    {
        ImGui::Text("%04X", i);
        ImGui::SameLine(0,0);
        ImGui::Text(": ");
        ImGui::SameLine(0,0);

        for (int j = 0; j < 15; j++)
        {
            ImGui::Text("%02X", 0xFF);
            ImGui::SameLine(0,0);
            ImGui::Text(" ");
            ImGui::SameLine(0,0);
            i++;
            if (j == 7)
            {
                ImGui::Text(" ");
                ImGui::SameLine(0,0);
            }
        }
        ImGui::Text("%02X", 0xFF);
        ImGui::SameLine(0,0);
        ImGui::Text(" ");
    }
    ImGui::End();
}