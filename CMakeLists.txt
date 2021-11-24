cmake_minimum_required(VERSION 3.21)
project("OpenGL")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor)

add_compile_definitions(GLEW_STATIC)

find_package(PkgConfig REQUIRED)

# Libraries
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
    include
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

add_executable(
    ${PROJECT_NAME} 
    "main.cpp"
    "src/shader.cpp"
    "src/renderer.cpp"
    "src/texture2d.cpp"
    "src/vertexArray.cpp"
    "src/indexbuffer.cpp"
    "src/vertexbuffer.cpp"
    "src/bufferLayout.cpp"
)

target_link_libraries(
    ${PROJECT_NAME}
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    ${OPENGL_LIBRARIES}
    vIMGUI
    vSTB_IMAGE
)

add_custom_target(
    copy_shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/shaders 
    ${CMAKE_CURRENT_BINARY_DIR}/shaders
)

add_custom_target(
    copy_textures
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/textures 
    ${CMAKE_CURRENT_BINARY_DIR}/textures
)

add_dependencies(
    ${PROJECT_NAME} 
    copy_shaders
    copy_textures
)
