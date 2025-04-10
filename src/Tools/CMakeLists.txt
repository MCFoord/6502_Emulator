project(tools)

set(CPU_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CPU)

# CPU Debugger
add_executable(CPUDebug
	${CPU_DIR}/CPUDebug.cpp
)

target_link_libraries(CPUDebug PRIVATE
    nes
)