cmake_minimum_required(VERSION 3.28.0)

project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(external)

add_executable(6502Emulator
    ${ROOT_DIR}/main.cpp
)

target_link_libraries(6502Emulator PRIVATE
    core
    gui
)
