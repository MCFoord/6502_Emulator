#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include "component.h"
#include "controller.h"

class Window
{
public:
    Window(Controller& controller);
    ~Window();
    void mainLoop();
    void drawFrame();
    void createNewHexView();
private:
    Controller& m_controller;
    GLFWwindow* m_window = nullptr;
    std::vector<Component*> m_components;
    bool initGlfw();
    bool initGlad();
    void initImGui();
    void terminateImGui();
    void terminateGlfw();
};