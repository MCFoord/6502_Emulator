project(gui)

set(COMPONENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/components)

add_library(gui STATIC
    window.cpp
    ${COMPONENTS_DIR}/hexview/hexview.cpp
    ${COMPONENTS_DIR}/controlpanel/controlpanel.cpp
)

target_include_directories(gui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COMPONENTS_DIR}
    ${COMPONENTS_DIR}/hexview
    ${COMPONENTS_DIR}/controlpanel
)

target_link_libraries(gui PUBLIC
    imgui
    glad
)

target_link_libraries(gui PRIVATE
    core
)