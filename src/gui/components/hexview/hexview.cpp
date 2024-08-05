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

    setSizes();
    drawHeader();
    drawMemory();

    ImGui::End();
}

void HexView::setSizes()
{
    m_sizes.addressCell = ImGui::CalcTextSize("FFFF: ");
    m_sizes.hexCell = ImGui::CalcTextSize("FF ");
    m_sizes.hexCellText = ImGui::CalcTextSize("FF");
    m_sizes.colMidPointSplit = ImGui::CalcTextSize(" ");
    m_sizes.lineHeight = ImGui::GetTextLineHeight();
    m_sizes.lineheightWithSpacing = ImGui::GetTextLineHeightWithSpacing();
}

bool HexView::clickInsideMemorywindow()
{
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 MemeoryWindowPos = ImVec2(windowPos.x + m_sizes.addressCell.x, windowPos.y - m_sizes.lineHeight * HEX_ROWS);
    ImVec2 MemoryWindowSize = ImVec2(ImGui::GetWindowSize().x - m_sizes.addressCell.x, m_sizes.lineHeight * HEX_ROWS);

    bool isInsideX = mousePos.x > MemeoryWindowPos.x && mousePos.x < (MemeoryWindowPos.x + MemoryWindowSize.x);
    bool isInsideY = mousePos.y > MemeoryWindowPos.y && mousePos.y < (MemeoryWindowPos.y + MemoryWindowSize.y);

    return isInsideX && isInsideY;
}

void HexView::drawHexcell(int value)
{
    ImGui::Text("%02X", value);
    ImGui::SameLine(0,0);
    ImGui::Text(" ");
    ImGui::SameLine(0,0);
}

void HexView::drawHeader()
{
    ImGui::BeginChild("header", ImVec2(-FLT_MIN, m_sizes.lineheightWithSpacing));

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + m_sizes.addressCell.x, ImGui::GetCursorPosY()));
    for (int col = 0; col < HEX_COLUMNS; col++)
    {
        drawHexcell(col);

        if (col == HEX_COL_MIDPOINT)
        {
            ImGui::Text(" ");
            ImGui::SameLine(0,0);
        }
    }
    ImGui::Text(" ");

    ImGui::EndChild();
}

void HexView::drawMemory()
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    
    ImGui::BeginChild(
        "memory", ImVec2(-FLT_MIN, m_sizes.lineHeight * HEX_ROWS),
        ImGuiChildFlags_None, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav
    );

    ImGuiListClipper clipper;
    clipper.Begin(MEM_SIZE / HEX_COLUMNS, m_sizes.lineHeight);

    while (clipper.Step())
    {
        if (clipper.DisplayStart != m_hexRangeStart | clipper.DisplayEnd != m_hexRangeEnd)
        {
            m_hexRangeStart = clipper.DisplayStart;
            m_hexRangeEnd = clipper.DisplayEnd;
        }

        m_baseLinePos = ImGui::GetCursorScreenPos();
        for (int line = clipper.DisplayStart; line < clipper.DisplayEnd; line++)
        {
            int addr = line * HEX_COLUMNS;
            ImGui::Text("%04X", addr);
            ImGui::SameLine(0,0);
            ImGui::Text(": ");
            ImGui::SameLine(0,0);

            for (int col = 0; col < HEX_COLUMNS && addr < MEM_SIZE; col++, addr++)
            {   
                if (addr == m_selectedAddress)
                {
                    ImVec2 pos = ImGui::GetCursorScreenPos();
                    drawList->AddRectFilled(pos, ImVec2(pos.x + m_sizes.hexCellText.x, pos.y + m_sizes.hexCellText.y), IM_COL32(255, 0, 0, 100));
                }

                drawHexcell(m_bus->read(addr));

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

    ImGui::BeginChild("footer", ImVec2(-FLT_MIN, m_sizes.lineheightWithSpacing * 2));

    if (ImGui::IsMouseClicked(0) && clickInsideMemorywindow())
    {
        ImVec2 mousePos = ImGui::GetMousePos();
        int lineDiff = (mousePos.y - m_baseLinePos.y) / m_sizes.lineheightWithSpacing;
        int colDiff = (mousePos.x - (m_baseLinePos.x + m_sizes.addressCell.x)) / (m_sizes.hexCell.x);
        if (colDiff > HEX_COL_MIDPOINT)
        {
            colDiff = (mousePos.x - (m_baseLinePos.x + m_sizes.addressCell.x + m_sizes.colMidPointSplit.x)) / (m_sizes.hexCell.x);
        }
        m_selectedLinebaseAddress = clipper.DisplayStart + (lineDiff * HEX_COLUMNS);
        m_selectedAddress = m_selectedLinebaseAddress + (colDiff);
    }

    ImGui::Text("%04X", m_selectedLinebaseAddress);
    ImGui::Text("%04X", m_selectedAddress);
    ImGui::EndChild();
}

void HexView::drawFooter()
{

}