project(nes)

set(6502_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CPU6502)
set(BUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bus)
set(CART_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Cartridge)
set(MAPPER_DIR ${CART_DIR}/Mappers)

add_library(nes STATIC
    ${6502_DIR}/CPU6502.cpp
    ${BUS_DIR}/Bus.cpp
    ${CART_DIR}/Cartridge.cpp
    ${MAPPER_DIR}/Mapper.cpp
)

target_include_directories(nes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${6502_DIR}
    ${BUS_DIR}
    ${CART_DIR}
    ${MAPPER_DIR}
)
