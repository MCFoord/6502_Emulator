#pragma once

#include <string>
#include "component.h"
#include "bus.h"
#include "imgui.h"

class HexView: public Component
{
public:
    HexView(std::string id, Bus* bus);
    ~HexView();
    void draw() override;
    int breakPoint;
private:
    std::string m_id;
    Bus* m_bus = nullptr;

    int m_hexRangeStart = 0;
    int m_hexRangeEnd = 0;
    int m_selectedLinebaseAddress = 0;
    int m_selectedAddress = 0;
    ImVec2 m_baseLinePos;

    struct sizes
    {
        ImVec2 hexCell;
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
};