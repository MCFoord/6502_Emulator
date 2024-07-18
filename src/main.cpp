#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "bus.h"
#include <sstream>
#include <iomanip>
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(6);

    // Create a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Window", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1; 
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set up ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Initialize ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Bus *bus = new Bus();
    bus->loadProgram(argv[1]);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create a simple ImGui window
        ImGui::Begin("Hello, world!");
        for (int i = 0x0000; i <= 0xFFFF; i++)
        {
            ImGui::Text("%04X", i);
            ImGui::SameLine(0,0);
            ImGui::Text(": ");
            ImGui::SameLine(0,0);

            for (int j = 0; j < 15; j++)
            {
                ImGui::Text("%02X", bus->read(i));
                ImGui::SameLine(0,0);
                ImGui::Text(" ");
                ImGui::SameLine(0,0);
                i++;
                if (j == 7)
                {
                    ImGui::Text(" ");
                    ImGui::SameLine(0,0);
                }
            }
            ImGui::Text("%02X", bus->read(i));
            ImGui::SameLine(0,0);
            ImGui::Text(" ");
        }
        
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
