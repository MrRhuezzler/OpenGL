// #define GLEW_STATIC
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Shader
{
    std::string vertexSrc;
    std::string fragmentSrc;
};


static Shader ParseShader(const std::string& filepath){

    std::cout << filepath << std::endl;
    std::fstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::string ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }else if(line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }else{
            if(type != ShaderType::NONE)
                ss[(int)type] += line + "\n";
        }
    }

    return {ss[0], ss[1]};

}

static unsigned int CompileShader(unsigned int type, std::string source){

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(!result){

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // Dynamic Allocation in stack memory
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Compiler Error ( " 
                  << (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader") 
                  << " )"
                  << std::endl;
        
        std::cout << message << std::endl;
        return 0;

    }

    return id;

}

static unsigned int createProgram(std::string vertexShader, std::string fragmentShader){

    unsigned int id = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glValidateProgram(id);

    return id;

}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err){
        std::cout << "[GLEW Error] : " << glewGetErrorString(err) << std::endl;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    // Vertex Buffers
    unsigned int buffer;
    // Creating a buffer
    glGenBuffers(1, &buffer);

    // Selecting a buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Setting the size of the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), &positions, GL_STATIC_DRAW);

    // Setting up how the memory should be interpreted ?
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    // Enable the vertex attribute
    glEnableVertexAttribArray(0);

    Shader source = ParseShader("Shaders/Basic.shader");
    unsigned int basicShaderProgram = createProgram(source.vertexSrc, source.fragmentSrc);
    glUseProgram(basicShaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Calls - Draws the current bound buffer.
        glDrawArrays(GL_TRIANGLES, 0, 6);

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

    glDeleteProgram(basicShaderProgram);

    glfwTerminate();
    return 0;
}