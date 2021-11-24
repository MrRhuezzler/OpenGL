#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"
#include "vertexArray.h"
#include "bufferLayout.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "[GLEW Error] : " << glewGetErrorString(err) << std::endl;
    }

    glfwSwapInterval(1);

    //ImGUI Initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    {

        float positions[] = {
            -0.5f,-0.5f,
            0.5f,-0.5f,
            0.5f,0.5f,
            -0.5f,0.5f,
        };

        // Indices array - Strictly Unsigned
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };


        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexArray vao;
        BufferLayout bl;
        bl.Add<float>(2, false);
        vao.AddBuffer(vb, bl);

        IndexBuffer ibo(indices, 6);
        Shader basicShaderProgram("Shaders/Basic.shader");

        // float r = 0.0f;
        // float increment = 0.01f;
        ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        while (!glfwWindowShouldClose(window))
        {

            // ImGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // ImGui::ShowDemoWindow(NULL);
            ImGui::Begin("Properties");
            ImGui::ColorEdit4("Color", (float*)&color);
            ImGui::End();

            basicShaderProgram.Bind();
            basicShaderProgram.SetUniform4f("u_Color", color.x, color.y, color.z, color.w);

            ImGui::Render();
            Renderer::Clear();
            Renderer::DrawElementsTris(vao, ibo, basicShaderProgram);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();

        }

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}