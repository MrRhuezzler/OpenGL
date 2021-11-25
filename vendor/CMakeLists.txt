cmake_minimum_required(VERSION 3.21)

project(Vendor)


# Libraries
### ImGUI
### stb_image
### glm

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# ImGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
message("-- vIMGUI : Static")
add_library(vIMGUI STATIC)

target_sources(vIMGUI
               PRIVATE
                ${IMGUI_DIR}/imgui.cpp
                ${IMGUI_DIR}/imgui_demo.cpp
                ${IMGUI_DIR}/imgui_draw.cpp
                ${IMGUI_DIR}/imgui_tables.cpp
                ${IMGUI_DIR}/imgui_widgets.cpp

                ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
                ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(vIMGUI
                           PUBLIC ${IMGUI_DIR}
                           PUBLIC ${IMGUI_DIR}/backends
)

target_link_libraries(
    vIMGUI
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# stb_image
set(STBIMAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb_image)
message("-- vSTB_IMAGE : Static")
add_library(vSTB_IMAGE STATIC)

target_sources(
    vSTB_IMAGE
    PRIVATE
        ${STBIMAGE_DIR}/stb_image.cpp
)

target_include_directories(
    vSTB_IMAGE
    PUBLIC ${STBIMAGE_DIR}/include
)

# glm
add_subdirectory(glm)