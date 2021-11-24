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