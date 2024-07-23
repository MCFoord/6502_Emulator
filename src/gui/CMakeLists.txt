project(gui)

add_library(gui STATIC
    window.cpp
)

target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gui PUBLIC
    imgui
    glad
)

target_link_libraries(gui PRIVATE
    6502
)