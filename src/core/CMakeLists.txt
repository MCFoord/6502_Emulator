project(core)

add_subdirectory(NesSystem)

set(CONTROLLER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Controller)

add_library(core STATIC
    ${CONTROLLER_DIR}/Controller.cpp
)

target_include_directories(core PUBLIC
    ${CONTROLLER_DIR}
)

target_link_libraries(core PUBLIC
    gui
    nes
)