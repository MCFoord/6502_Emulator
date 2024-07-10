project(6502)


add_library(6502 STATIC
    cpu6502.cpp
    bus.cpp
)

target_include_directories(6502 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
