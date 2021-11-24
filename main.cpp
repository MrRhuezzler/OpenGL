#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "renderer.h"
#include "texture2d.h"
#include "indexbuffer.h"
#include "vertexArray.h"
#include "vertexbuffer.h"
#include "bufferLayout.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Square
        // float positions[] = {
        //     -0.5f,-0.5f, 0.0f, 0.0f,
        //     0.5f,-0.5f, 1.0f, 0.0f,
        //     0.5f,0.5f, 1.0f, 1.0f,
        //     -0.5f,0.5f, 0.0f, 1.0f
        // };

        // Circular Triangles
        float positions[] = {
             0.00f,  0.00f,
             0.25f, -0.50f,
             0.50f, -0.25f,
             0.50f,  0.25f,
             0.25f,  0.50f,
            -0.25f,  0.50f,
            -0.50f,  0.25f,
            -0.50f, -0.25f,
            -0.25f, -0.50f,
        };

        // Indices array - Strictly Unsigned
        // Square
        // unsigned int indices[] = {
        //     0, 1, 2,
        //     2, 3, 0
        // };

        // Circular Triangles
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 5,
            0, 5, 6,
            0, 6, 7,
            0, 7, 8,
            0, 8, 1,
        };

        VertexBuffer vb(positions, 9 * 2 * sizeof(float));

        VertexArray vao;
        BufferLayout bl;
        bl.Add<float>(2, false);
        vao.AddBuffer(vb, bl);

        IndexBuffer ibo(indices, 8 * 3);
        Shader basicShaderProgram("shaders/basic.shader");
        // Shader texture2dProgram("shaders/texture2d.shader");

        // Texture2D tex("textures/logo.png");
        // tex.Bind();

        // texture2dProgram.Bind();
        // texture2dProgram.SetUniform1i("u_Texture2D", 0);

        ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImVec4 clearColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        while (!glfwWindowShouldClose(window))
        {

            // ImGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // ImGui::ShowDemoWindow(NULL);
            ImGui::Begin("Properties");
            ImGui::ColorEdit4("Clear Color", (float*)&clearColor);
            ImGui::ColorEdit4("Square Color", (float*)&color);
            ImGui::End();

            basicShaderProgram.Bind();
            basicShaderProgram.SetUniform4f("u_Color", color.x, color.y, color.z, color.w);

            ImGui::Render();
            Renderer::SetClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
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