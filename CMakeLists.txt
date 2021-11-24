cmake_minimum_required(VERSION 3.21)
project("OpenGL")

set(CMAKE_CXX_STANDARD 17)

# ImGUI Compilation
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
add_library(ImGUI STATIC)

target_sources(ImGUI
               PRIVATE
                ${IMGUI_DIR}/imgui.cpp
                ${IMGUI_DIR}/imgui_demo.cpp
                ${IMGUI_DIR}/imgui_draw.cpp
                ${IMGUI_DIR}/imgui_tables.cpp
                ${IMGUI_DIR}/imgui_widgets.cpp

                ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
                ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImGUI
                           PUBLIC ${IMGUI_DIR}
                           PUBLIC ${IMGUI_DIR}/backends
)

target_link_libraries(
    ImGUI
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# Binary Compilation

add_compile_definitions(GLEW_STATIC)

find_package(PkgConfig REQUIRED)

# Libraries
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
    "include/"
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${ImGUI_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

add_executable(
    ${PROJECT_NAME} 
    "main.cpp"
    "src/shader.cpp"
    "src/renderer.cpp"
    "src/indexbuffer.cpp"
    "src/vertexbuffer.cpp"
    "src/vertexArray.cpp"
    "src/bufferLayout.cpp"
)

target_link_libraries(
    ${PROJECT_NAME}
    ImGUI 
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    ${OPENGL_LIBRARIES}
)

add_custom_target(
    copy_shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/Shaders 
    ${CMAKE_CURRENT_BINARY_DIR}/Shaders
)

add_dependencies(
    ${PROJECT_NAME} 
    copy_shaders
)
