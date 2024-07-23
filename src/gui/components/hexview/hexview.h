#pragma once

#include <string>
#include "component.h"

class HexView: public Component
{
public:
    HexView(std::string id);
    ~HexView();
    void draw() override;
private:
    //sizes
    std::string m_id;
};