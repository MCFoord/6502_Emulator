#pragma once

#include "Bus.h"
#include "CPU6502.h"
#include "Cartridge.h"
#include <memory>

class NESSystem
{
    public:
        NESSystem();
        ~NESSystem();

    private:
        std::shared_ptr<Bus> m_bus = nullptr;
        std::shared_ptr<CPU6502> m_CPU = nullptr;
        std::shared_ptr<Cartridge> m_cartridge = nullptr;

        void tick();
        void powerOn();
        void reset();
        bool LoadCartridge(std::filesystem::path path);
};