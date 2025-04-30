#pragma once

#include <atomic>
#include <vector>
#include <GLFW/glfw3.h>
#include "Component.h"
#include "Controller.h"

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
    std::atomic_int m_nComponents = 0;

    bool initGlfw();
    bool initGlad();
    void initImGui();
    void mainLoop();
    void drawFrame();
    void terminateImGui();
    void terminateGlfw();
};