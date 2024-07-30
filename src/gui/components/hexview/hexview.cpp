#include "hexview.h"
#include "imgui.h"

#define HEX_COLUMNS 16
#define HEX_ROWS 16
#define MEM_SIZE 64 * 1024
#define HEX_COL_MIDPOINT 7

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
    ImGui::Begin(m_id.c_str());

    drawMemory();
    ImGui::End();
}

void HexView::drawMemory()
{
    ImGui::BeginChild("##scrolling", ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * HEX_ROWS));
    ImGuiListClipper clipper;
    clipper.Begin(MEM_SIZE / HEX_COLUMNS, ImGui::GetTextLineHeight());
    while (clipper.Step())
    {
        int addr = clipper.DisplayStart;
        for (int line = clipper.DisplayStart; line < clipper.DisplayEnd; line++)
        {
            int addr = line * HEX_COLUMNS;
            ImGui::Text("%04X", addr);
            ImGui::SameLine(0,0);
            ImGui::Text(": ");
            ImGui::SameLine(0,0);

            for (int col = 0; col < HEX_COLUMNS && addr < MEM_SIZE; col++, addr++)
            {
                ImGui::Text("%02X", m_bus->read(addr));
                ImGui::SameLine(0,0);
                ImGui::Text(" ");
                ImGui::SameLine(0,0);
                if (col == HEX_COL_MIDPOINT)
                {
                    ImGui::Text(" ");
                    ImGui::SameLine(0,0);
                }
            }
            ImGui::Text(" ");
        }
    }
    ImGui::EndChild();
    ImGui::BeginChild("##footer");
    ImGui::Text("%04X",clipper.DisplayStart);
    ImGui::Text("%04X",clipper.DisplayEnd);
    ImGui::EndChild();
    
}