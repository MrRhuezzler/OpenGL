#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <unordered_map>

class Shader {

    std::string filepath;
    unsigned int id;

    std::unordered_map<std::string, int> uniforms;

    public:
        struct shaderSources {
            std::string vertexSource;
            std::string fragmentSource;
        };

        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void SetUniform1i(std::string name, int value);
        void SetUniform4f(std::string name, float x, float y, float z, float w);
        void SetUniformMat4(std::string name, const float* mat4);

    private:
        unsigned int compileShader(unsigned int type, std::string source);
        shaderSources parseShader(const std::string& filepath);
        int getUniformLocation(std::string name);

};

#endif // __SHADER_H__