project(core)

set(6502_DIR ${CMAKE_CURRENT_SOURCE_DIR}/6502)
set(CONTROLLER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/controller)

add_library(core STATIC
    ${CONTROLLER_DIR}/controller.cpp
    ${6502_DIR}/cpu6502.cpp
    ${6502_DIR}/bus.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CONTROLLER_DIR}
    ${6502_DIR}
)

target_link_libraries(core PRIVATE
    gui
)