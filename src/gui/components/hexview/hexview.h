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
    void drawMemory();
    int breakPoint;
private:
    std::string m_id;
    Bus* m_bus = nullptr;

    // struct lineBaseAddressBoundary
    // {
    //     int address;
    //     ImVec2 boundary;
    // };

    //kind of misusing the imvec here, maybe change
    int m_hexRangeStart = 0;
    int m_hexRangeEnd = 0;
    int m_selectedLinebaseAddress = 0;
    ImVec2 m_baseLinePos;
};