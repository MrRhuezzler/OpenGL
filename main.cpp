// #define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err){
        // fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        std::cout << "[GLEW Error] : " << glewGetErrorString(err) << std::endl;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        0, 1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f
    };

    // Vertex Buffers
    unsigned int buffer;
    // Creating a buffer
    glGenBuffers(1, &buffer);
    
    // Selecting a buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Setting the size of the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &positions, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Calls - Draws the current bound buffer.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Legacy OpenGL
        // glBegin(GL_TRIANGLES);
        // glVertex2d(0, 1.0f);
        // glVertex2d(1.0f, -1.0f);
        // glVertex2d(-1.0f, -1.0f);
        // glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}