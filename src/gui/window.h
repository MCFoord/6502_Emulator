#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class Window
{
public:
    Window();
    ~Window();
    void mainLoop();
    void drawFrame();

private:
    GLFWwindow* m_window = nullptr;
    bool initGlfw();
    bool initGlad();
    void initImGui();
    void terminateImGui();
    void terminateGlfw();
};