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
