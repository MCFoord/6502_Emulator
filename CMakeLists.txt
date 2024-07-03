cmake_minimum_required(VERSION 3.16.0)

project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../src")

find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)

set(6502_DIR "${ROOT_DIR}/6502")

include_directories(
    ${6502_DIR}
)

set(6502_SOURCES
    ${6502_DIR}/cpu6502.cpp
    ${6502_DIR}/bus.cpp
    ${ROOT_DIR}/main.cpp
)

set(INTERFACE_SOURCES
    
)

set(6502_INCLUDES
    ${6502_DIR}/bus.h
    ${6502_DIR}/cpu6502.h
)


add_executable(6502Emulator
    ${6502_SOURCES}
    ${6502_INCLUDES}
)
