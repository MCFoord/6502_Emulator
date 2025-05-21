
add_library(renderer STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(renderer PUBLIC
    OpenGL
	glad
    glfw
)