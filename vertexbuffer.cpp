#include <GL/glew.h>

#include "renderer.h"
#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::Bind() const
{
     GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
