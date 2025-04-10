#pragma once

#include "Bus.h"
#include "CPU6502.h"

class NESSystem
{
    public:
        NESSystem();
        ~NESSystem();

    private:
        Bus* bus = nullptr;
        CPU6502* CPU = nullptr;

        void tick();
        void powerOn();
        void reset();
};