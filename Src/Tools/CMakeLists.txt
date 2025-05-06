project(tools)

set(CPU_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CPU)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../")

# CPU Debugger
add_executable(CPUDebug
	${CPU_DIR}/CPUDebug.cpp
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(CPUDebug PRIVATE
    nes
	${CURSES_LIBRARIES}
)