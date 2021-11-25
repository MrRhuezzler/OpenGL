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

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

int width = 800;
int height = 600;

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
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
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

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Cube
        float positions[] = {
            
        };

        // Indices array - Strictly Unsigned
        // Square
        unsigned int indices[] = {

        };

        VertexBuffer vb(positions, sizeof(positions));

        VertexArray vao;
        BufferLayout bl;
        bl.Add<float>(3, false);
        vao.AddBuffer(vb, bl);

        IndexBuffer ibo(indices, 12 * 3);
        Shader shader("shaders/proj.shader");

        // Projections, View, Model
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), float(width / height), 0.01f, 10.0f);
        glm::mat4 model(1.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));

        ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImVec4 clearColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        while (!glfwWindowShouldClose(window))
        {

            // ImGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Properties");
            ImGui::ColorEdit4("Clear Color", (float*)&clearColor);
            ImGui::ColorEdit4("Square Color", (float*)&color);
            ImGui::End();

            ImGui::Render();
            Renderer::SetClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
            Renderer::Clear();

            // Set Uniforms
            shader.Bind();
            shader.SetUniformMat4("u_Model", glm::value_ptr(model));
            shader.SetUniformMat4("u_View", glm::value_ptr(view));
            shader.SetUniformMat4("u_Projection", glm::value_ptr(proj));

            model = glm::rotate(model, 0.02f, glm::vec3(0.0, 1.0, 0.0));
            model = glm::rotate(model, 0.01f, glm::vec3(0.0, 0.0, 1.0));

            Renderer::DrawElementsTris(vao, ibo, shader);
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