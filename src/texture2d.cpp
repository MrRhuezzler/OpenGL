#include <GL/glew.h>

#include "texture2d.h"
#include "renderer.h"

#include "stb_image.h"

Texture2D::Texture2D(const std::string& path)
:filePath(path), width(0), height(0), localBuffer(nullptr), BPP(0)
{

    // Flips the image vertically.
    // OpenGL expects the 0,0 to be on the bottom left
    stbi_set_flip_vertically_on_load(1);

    localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

    GLCall(glGenTextures(1, &id));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    // internal format => How Opengl stores
    // format => Format of the data the is being given
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(localBuffer)
        stbi_image_free(localBuffer);

}

Texture2D::~Texture2D()
{
    GLCall(glDeleteTextures(1, &id));
}


void Texture2D::Bind(unsigned int slot /* = 0*/) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture2D::UnBind() const{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
