#include "NesSystem.h"
#include "CPU6502.h"
#include "Cartridge.h"
#include <memory>
#include <iostream>

NESSystem::NESSystem()
{
    m_bus = std::make_shared<Bus>();
    m_CPU = std::make_unique<CPU6502>();
    m_CPU->connectBus(m_bus);
}

NESSystem::~NESSystem()
{

}

void NESSystem::tick()
{
    m_CPU->tick();
}

void NESSystem::reset()
{

}

void NESSystem::powerOn()
{
    
}

bool NESSystem::LoadCartridge(std::filesystem::path path)
{
    std::cout << "creating new cartridge from file\n";

    m_cartridge = std::make_shared<Cartridge>(path);

    if (m_cartridge->successfulLoad())
        m_bus->connectCartridge(m_cartridge);

    std::cout << "loaded successfully? " << m_cartridge->successfulLoad() << "\n";
    return m_cartridge->successfulLoad();
}

void NESSystem::UnloadCartridge()
{
    m_bus->disconnectCartridge();
    m_cartridge = nullptr;
}