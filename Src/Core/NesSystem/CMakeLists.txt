project(nes)

set(6502_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CPU6502)
set(PPU_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PPU)
set(BUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bus)
set(CART_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Cartridge)
set(MAPPER_DIR ${CART_DIR}/Mappers)

add_library(nes STATIC
    NesSystem.cpp
    ${6502_DIR}/CPU6502.cpp
    ${PPU_DIR}/PPU.cpp
    ${BUS_DIR}/Bus.cpp
    ${CART_DIR}/Cartridge.cpp
    ${MAPPER_DIR}/Mapper.cpp
)

target_include_directories(nes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${6502_DIR}
    ${PPU_DIR}
    ${BUS_DIR}
    ${CART_DIR}
    ${MAPPER_DIR}
)
