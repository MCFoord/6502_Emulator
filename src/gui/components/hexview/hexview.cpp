#include "hexview.h"
#include "imgui.h"

HexView::HexView(std::string id, Bus* bus):
m_id(id),
m_bus(bus)
{
    
}

HexView::~HexView()
{

}

void HexView::draw()
{
    //change this to be dependant on ram size
    //and just change it to be better anyway
    ImGui::Begin(m_id.c_str());
    for (int i = 0x0000; i <= 0xFFFF; i++)
    {
        ImGui::Text("%04X", i);
        ImGui::SameLine(0,0);
        ImGui::Text(": ");
        ImGui::SameLine(0,0);

        for (int j = 0; j < 15; j++)
        {
            ImGui::Text("%02X", m_bus->read(i));
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
        ImGui::Text("%02X", m_bus->read(i));
        ImGui::SameLine(0,0);
        ImGui::Text(" ");
    }
    ImGui::End();
}

void HexView::drawMemory()
{
    ImGui::BeginChild("##scrolling");
    
    ImGui::EndChild();
}