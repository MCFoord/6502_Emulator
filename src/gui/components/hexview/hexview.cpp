#include "hexview.h"
#include "imgui.h"
#include <iostream>

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
    ImGui::BeginChild("##scrolling", ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * HEX_ROWS), ImGuiChildFlags_None, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav);
    ImGuiListClipper clipper;
    clipper.Begin(MEM_SIZE / HEX_COLUMNS, ImGui::GetTextLineHeight());

    while (clipper.Step())
    {

        if (clipper.DisplayStart != m_hexRangeStart | clipper.DisplayEnd != m_hexRangeEnd)
        {
            m_hexRangeStart = clipper.DisplayStart;
            m_hexRangeEnd = clipper.DisplayEnd;
        }

        m_baseLinePos = ImGui::GetCursorPos();
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
    if (ImGui::IsMouseClicked(0))
    {
        ImVec2 mousePos = ImGui::GetMousePos();
        int lineDiff = (mousePos.x - m_baseLinePos.x) / ImGui::GetTextLineHeight();
        m_selectedLinebaseAddress = clipper.DisplayStart + (lineDiff * HEX_COLUMNS);
        std::cout << m_selectedLinebaseAddress << '\n';
    }

    ImGui::Text("%04X", m_selectedLinebaseAddress);
    ImGui::Text("%04X", clipper.DisplayEnd);
    ImGui::EndChild();
    
}