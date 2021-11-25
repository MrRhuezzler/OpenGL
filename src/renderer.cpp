#include <iostream>
#include <GL/glew.h>

#include "renderer.h"

void GLClearErrors(){
    while(glGetError());
}

bool GLLogError(const char* function, const char* file, int line){

    bool errorOccured = true;
    while(GLenum err = glGetError()){
        std::cout << "[OPENGL][ERROR] " << function << std::endl;
        std::cout << "[OPENGL][ERROR] " << file << " : " << line << std::endl;
        std::cout << "[OPENGL][ERROR] ( "<< err << " )" << std::endl;
        errorOccured = false;
    }
    return errorOccured;

}

void Renderer::SetClearColor(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
}

void Renderer::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawElementsTris(const VertexArray& va, const IndexBuffer& ib, const Shader& shader){
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
