#include <GL/glew.h>

#include "renderer.h"
#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
:count(count)
{
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() 
{
    GLCall(glDeleteBuffers(1, &id));
}

void IndexBuffer::Bind() const
{
     GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const {
    return count;
}