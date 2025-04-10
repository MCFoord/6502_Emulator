project(nes)

set(6502_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CPU6502)
set(BUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bus)

add_library(nes STATIC
    ${6502_DIR}/CPU6502.cpp
    ${BUS_DIR}/Bus.cpp
)

target_include_directories(nes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${6502_DIR}
    ${BUS_DIR}
)
