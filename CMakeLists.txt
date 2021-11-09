cmake_minimum_required(VERSION 3.21)
project("OPENGL")

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(GLEW_STATIC)

find_package(PkgConfig REQUIRED)

# Libraries
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
    ${GLFW_INCLUDE_DIRS} 
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS} 
)

add_executable(${PROJECT_NAME}   "main.cpp"
                "renderer.h"     "renderer.cpp" 
                "vertexbuffer.h" "vertexbuffer.cpp"
                "indexbuffer.h"  "indexbuffer.cpp")

target_link_libraries(
    ${PROJECT_NAME} 
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

add_dependencies(${PROJECT_NAME} copy_shaders)
