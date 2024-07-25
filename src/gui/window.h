#pragma once

#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "component.h"
#include "bus.h"
#include "cpu6502.h"


class Window
{
public:
    Window();
    ~Window();
    void mainLoop();
    void drawFrame();
    void createNewHexView();
private:
    GLFWwindow* m_window = nullptr;
    std::vector<Component*> m_components;
    Bus bus;
    CPU6502 cpu;
    bool initGlfw();
    bool initGlad();
    void initImGui();
    void terminateImGui();
    void terminateGlfw();
};