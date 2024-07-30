#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <mutex>
#include <condition_variable>
#include "component.h"
#include "bus.h"
#include "cpu6502.h"
#include "cpuoption.h"


class Window
{
public:
    Window(
        Bus* bus, std::mutex& mtx, std::condition_variable& cv,
        bool& optionSet, CpuOption& option
    );
    ~Window();
    void mainLoop();
    void drawFrame();
    void createNewHexView();
private:
    GLFWwindow* m_window = nullptr;
    std::vector<Component*> m_components;
    Bus* m_bus = nullptr;
    bool initGlfw();
    bool initGlad();
    void initImGui();
    void terminateImGui();
    void terminateGlfw();
};