project(imgui)

set(IMGUI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_SOURCE_DIR}/backends)
set(IMGUI_LIBS_DIR ${IMGUI_SOURCE_DIR}/examples/libs)

set(IMGUI_SOURCE_FILES
    ${IMGUI_SOURCE_DIR}/examples/example_glfw_opengl3/main.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    # ${GL3W_SOURCE_DIR}/GL/gl3w.c
)

add_library(imgui STATIC
    ${IMGUI_SOURCE_DIR}
)

target_include_directories(imgui PRIVATE
    ${IMGUI_SOURCE_DIR}
    ${IMGUI_BACKENDS_DIR}
    # ${GLFW_INCLUDE_DIR}
    # ${GL3W_SOURCE_DIR}
)

find_package(OpenGL REQUIRED)

target_link_libraries(imgui
    OpenGL::GL
    glfw
)




