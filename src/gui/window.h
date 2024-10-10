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
    void createNewHexView();
    void setProgramToQuit();
private:
    Controller& m_controller;
    GLFWwindow* m_window = nullptr;
    std::vector<Component*> m_components;
    bool m_quitProgram = false;

    bool initGlfw();
    bool initGlad();
    void initImGui();
    void mainLoop();
    void drawFrame();
    void terminateImGui();
    void terminateGlfw();
};