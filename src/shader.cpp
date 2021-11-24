#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "renderer.h"
#include "shader.h"

Shader::Shader(const std::string& filepath){

    GLCall(id = glCreateProgram());
    Shader::shaderSources src = parseShader(filepath);
    unsigned int vs = compileShader(GL_VERTEX_SHADER, src.vertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, src.fragmentSource);

    GLCall(glAttachShader(id, vs));
    GLCall(glAttachShader(id, fs));
    GLCall(glLinkProgram(id));
    GLCall(glValidateProgram(id));

}

Shader::~Shader(){
    GLCall(glDeleteProgram(id));
}

void Shader::Bind() const {
    GLCall(glUseProgram(id));   
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

Shader::shaderSources Shader::parseShader(const std::string& filepath)
{

    std::fstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::string ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type] += line + "\n";
        }
    }

    return {ss[0], ss[1]};
}

unsigned int Shader::compileShader(unsigned int type, std::string source)
{

    GLCall(unsigned int s_id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(s_id, 1, &src, nullptr));
    GLCall(glCompileShader(s_id));

    int result;
    glGetShaderiv(s_id, GL_COMPILE_STATUS, &result);

    if (!result)
    {

        int length;
        glGetShaderiv(s_id, GL_INFO_LOG_LENGTH, &length);

        // Dynamic Allocation in stack memory
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(s_id, length, &length, message);

        std::cout << "Compiler Error ( "
                  << (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader")
                  << " )"
                  << std::endl;

        std::cout << message << std::endl;
        return 0;
    }

    return s_id;
}
