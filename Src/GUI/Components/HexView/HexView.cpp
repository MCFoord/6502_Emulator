#include "HexView.h"
#include "Controller.h"
#include "imgui.h"

// make a bunch of these configurable
#define HEX_COLUMNS 16
#define HEX_ROWS 16
#define MEM_SIZE 64 * 1024
#define HEX_COL_MIDPOINT 7
#define SELECTED_HIGHLIGHT_COLOUR IM_COL32(0, 255, 0, 100)
#define BREAKPOINT_HIGHLIGHT_COLOUR IM_COL32(255, 0, 0, 100)

HexView::HexView(std::string id, Window* parent, Controller& controller):
m_id(id),
m_parent(parent),
m_controller(controller),
m_getMemSizeFunction(&Controller::CPURAMSize),
m_readMemFunction(&Controller::CPURAMRead)
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
    drawFooter();

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
    ImVec2 MemeoryWindowPos = ImVec2(
        windowPos.x + m_sizes.addressCell.x,
        windowPos.y - m_sizes.lineHeight * HEX_ROWS
    );
    ImVec2 MemoryWindowSize = ImVec2(
        ImGui::GetWindowSize().x - m_sizes.addressCell.x,
        m_sizes.lineHeight * HEX_ROWS
    );

    bool isInsideX = mousePos.x > MemeoryWindowPos.x && mousePos.x < (MemeoryWindowPos.x + MemoryWindowSize.x);
    bool isInsideY = mousePos.y > MemeoryWindowPos.y && mousePos.y < (MemeoryWindowPos.y + MemoryWindowSize.y);

    return isInsideX && isInsideY;
}

void HexView::calcSelectedAddress()
{
    ImVec2 mousePos = ImGui::GetMousePos();
    int lineDiff = (mousePos.y - m_baseLinePos.y) / m_sizes.lineheightWithSpacing;
    int colDiff = (mousePos.x - (m_baseLinePos.x + m_sizes.addressCell.x)) / (m_sizes.hexCell.x);

    if (colDiff > HEX_COL_MIDPOINT)
    {
        colDiff = (mousePos.x - (m_baseLinePos.x + m_sizes.addressCell.x + m_sizes.colMidPointSplit.x)) / (m_sizes.hexCell.x);
    }

    m_selectedLinebaseAddress = m_visibleBaseAddress + (lineDiff * HEX_COLUMNS);
    m_selectedAddress = m_selectedLinebaseAddress + (colDiff);
}

void HexView::colourCell(ImU32 colour, ImDrawList* dl)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    dl->AddRectFilled(pos, ImVec2(pos.x + m_sizes.hexCellText.x, pos.y + m_sizes.hexCellText.y), colour);
}

void HexView::drawHexcell(int value)
{
    ImGui::Text("%02X ", value);
    ImGui::SameLine(0,0);
}

void HexView::drawHeader()
{
    ImGui::BeginChild("header", ImVec2(-FLT_MIN, m_sizes.lineheightWithSpacing));

    ImGui::SetCursorPos(ImVec2(
        ImGui::GetCursorPosX() + m_sizes.addressCell.x,
        ImGui::GetCursorPosY()
    ));
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
    const uint64_t memorySize = (m_controller.*m_getMemSizeFunction)();

    clipper.Begin(memorySize / HEX_COLUMNS, m_sizes.lineHeight);

    while (clipper.Step())
    {
        if (clipper.DisplayStart != m_hexRangeStart | clipper.DisplayEnd != m_hexRangeEnd)
        {
            m_hexRangeStart = clipper.DisplayStart;
            m_hexRangeEnd = clipper.DisplayEnd;
        }

        m_baseLinePos = ImGui::GetCursorScreenPos();
        m_visibleBaseAddress = clipper.DisplayStart * HEX_COLUMNS;
        for (int line = clipper.DisplayStart; line < clipper.DisplayEnd; line++)
        {
            int addr = line * HEX_COLUMNS;
            ImGui::Text("%04X: ", addr);
            ImGui::SameLine(0,0);

            for (int col = 0; col < HEX_COLUMNS && addr < memorySize; col++, addr++)
            {   
                if (m_controller.isBreakpoint(addr))
                {
                    colourCell(BREAKPOINT_HIGHLIGHT_COLOUR, drawList);
                }
                else if (addr == m_selectedAddress)
                {
                    colourCell(SELECTED_HIGHLIGHT_COLOUR, drawList);
                }

                drawHexcell((m_controller.*m_readMemFunction)(addr));

                if (col == HEX_COL_MIDPOINT)
                {
                    ImGui::Text(" ");
                    ImGui::SameLine(0,0);
                }
            }
            ImGui::NewLine();
        }
    }

    ImGui::EndChild();
}

void HexView::drawFooter()
{
    ImGui::BeginChild("footer", ImVec2(-FLT_MIN, m_sizes.lineheightWithSpacing * 3));

    if (ImGui::IsMouseClicked(0) && clickInsideMemorywindow())
    {
        calcSelectedAddress();
    }

    if (ImGui::Button("Set Breakpoint") && m_selectedAddress != -1)
    {
        m_controller.addBreakpoint(m_selectedAddress);
    }

    ImGui::SameLine();

    if (ImGui::Button("Remove Breakpoint"))
    {
        m_controller.removeBreakpoint(m_selectedAddress);
    }

    // ImGui::SameLine();
    
    if (ImGui::Button("Full CPU Address Space"))
    {
        m_getMemSizeFunction = &Controller::CPUFullAddressSpaceSize;
        m_readMemFunction = &Controller::CPURead;
    }

    ImGui::SameLine();

    if (ImGui::Button("PRG ROM"))
    {
        m_getMemSizeFunction = &Controller::cartridgePRGROMSize;
        m_readMemFunction = &Controller::cartridgePRGROMRead;
    }

    ImGui::SameLine();

    if (ImGui::Button("PRG RAM"))
    {
        m_getMemSizeFunction = &Controller::cartridgePRGRAMSize;
        m_readMemFunction = &Controller::cartridgePRGRAMRead;
    }

    ImGui::SameLine();

    if (ImGui::Button("CHR RAM"))
    {
        m_getMemSizeFunction = &Controller::cartridgeCHRRAMSize;
        m_readMemFunction = &Controller::cartridgeCHRRAMRead;
    }

    ImGui::SameLine();

    if (ImGui::Button("CPU RAM"))
    {
        m_getMemSizeFunction = &Controller::CPURAMSize;
        m_readMemFunction = &Controller::CPURAMRead;
    }


    ImGui::EndChild();
}