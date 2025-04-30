#include "NesSystem.h"
#include "CPU6502.h"
#include "Cartridge.h"
#include <memory>

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
    m_cartridge = std::make_shared<Cartridge>(path);

    if (m_cartridge->successfulLoad())
        m_bus->connectCartridge(m_cartridge);

    return m_cartridge->successfulLoad();
}

void NESSystem::UnloadCartridge()
{
    m_bus->disconnectCartridge();
    m_cartridge = nullptr;
}