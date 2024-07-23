#pragma once

class Component
{
public:
    virtual void draw() = 0;
    virtual ~Component() = default;
};