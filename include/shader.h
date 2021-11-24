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

        void SetUniform4f(std::string name, float x, float y, float z, float w);
        // GLCall(glUniform4f(u_Color, r, 0.3, 0.5f, 1.0f));

    private:
        unsigned int compileShader(unsigned int type, std::string source);
        shaderSources parseShader(const std::string& filepath);

};

#endif // __SHADER_H__