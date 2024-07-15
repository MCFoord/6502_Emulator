cmake_minimum_required(VERSION 3.30.0)

project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(external)

add_executable(6502Emulator
    ${ROOT_DIR}/main.cpp
)

target_link_libraries(6502Emulator PRIVATE
    6502
    # interface
    IMGUI
    glad
)



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)



project(IMGUI)

set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
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

add_library(IMGUI STATIC
    ${IMGUI_SOURCE_FILES}
)

target_include_directories(IMGUI PUBLIC
    ${IMGUI_SOURCE_DIR}
    ${IMGUI_BACKENDS_DIR}
)

target_link_libraries(IMGUI
    glfw
)
