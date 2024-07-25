#include <iostream>
#include "window.h"
#include "controlpanel.h"
#include "hexview.h"


Window::Window()
{
    initGlfw();
    initGlad();
    initImGui();

    bus = Bus();
    cpu = CPU6502();

    //As everthing is owned by window, all pointers should be cleaned up when window is destroyed
    //Should probably change this to a shared pointer though just in case
    cpu.connectBus(&bus);
    Component* controls = new ControlPanel("Controls", &cpu, &bus, this);
    m_components.push_back(controls);
    mainLoop();
}

Window::~Window()
{
    terminateImGui();
    terminateGlfw();

    for (Component* component : m_components)
    {
        delete component;
    }

    m_components.clear();
}

bool Window::initGlfw()
{

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(800, 600, "ImGui Window", nullptr, nullptr);
    if (m_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    return true;
}

bool Window::initGlad()
{
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Window::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::createNewHexView()
{
    std::string hexViewId = "RAM" + m_components.size();
    m_components.push_back(new HexView(hexViewId, &bus));
}

void Window::drawFrame()
{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto& component : m_components)
        {
            component->draw();
        }
}

void Window::mainLoop()
{
    while (!glfwWindowShouldClose(m_window)) {
        // Input
        glfwPollEvents();

        drawFrame();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  

        // Swap buffers
        glfwSwapBuffers(m_window);
    }
}

void Window::terminateImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Window::terminateGlfw()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}