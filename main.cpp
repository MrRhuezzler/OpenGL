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

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

        float r = 0.0f;
        float increment = 0.01f;

        while (!glfwWindowShouldClose(window))
        {

            Renderer::Clear();

            basicShaderProgram.Bind();
            basicShaderProgram.SetUniform4f("u_Color", r, 0.3, 0.5, 1.0);

            Renderer::DrawElementsTris(vao, ibo, basicShaderProgram);

            if(r > 1.0f || r < 0.0f){
                increment = (-1.0f * increment);
            }
            r += increment;

            glfwSwapBuffers(window);
            glfwPollEvents();

        }

    }

    glfwTerminate();
    return 0;
}