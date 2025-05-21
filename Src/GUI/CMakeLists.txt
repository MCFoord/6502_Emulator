project(gui)

set(COMPONENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Components)

add_library(gui STATIC
    Window.cpp
    ${COMPONENTS_DIR}/HexView/HexView.cpp
    ${COMPONENTS_DIR}/ControlPanel/ControlPanel.cpp
)

target_include_directories(gui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COMPONENTS_DIR}
    ${COMPONENTS_DIR}/HexView
    ${COMPONENTS_DIR}/ControlPanel
)

target_link_libraries(gui PUBLIC
    imgui
    glad
)

target_link_libraries(gui PRIVATE
    core
)