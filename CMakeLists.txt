cmake_minimum_required(VERSION 3.28.0)

project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${PROJECT_SOURCE_DIR}/Src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Src)
add_subdirectory(External)


add_executable(6502Emulator
    ${ROOT_DIR}/main.cpp
)

target_link_libraries(6502Emulator PRIVATE
    core
    gui
)