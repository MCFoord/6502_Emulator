#pragma once

#include <string>
#include "Component.h"
#include "imgui.h"
#include "Controller.h"
#include "Window.h"

class HexView: public Component
{
public:
    HexView(std::string id, Window* parent, Controller& controller);
    ~HexView();
    void draw() override;
    int m_breakPoint = -1;
private:
    std::string m_id;
    Window* m_parent;
    Controller& m_controller;

    int m_hexRangeStart = 0;
    int m_hexRangeEnd = 0;
    int m_visibleBaseAddress = 0;
    int m_selectedLinebaseAddress = 0;
    int m_selectedAddress = -1;
    ImVec2 m_baseLinePos;

    struct sizes
    {
        ImVec2 hexCell;
        ImVec2 hexCellText;
        ImVec2 addressCell;
        ImVec2 colMidPointSplit;
        float lineHeight;
        float lineheightWithSpacing;
    };

    sizes m_sizes;

    void setSizes();
    void drawHexcell(int value);
    void drawHeader();
    void drawMemory();
    void drawFooter();
    bool clickInsideMemorywindow();
    void calcSelectedAddress();
    void colourCell(ImU32 colour, ImDrawList* dl);
};