#include "vertexArray.h"
#include "renderer.h"

VertexArray::VertexArray() 
{
    GLCall(glGenVertexArrays(1, &id));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &id));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& bl) 
{
    Bind();
    vb.Bind();
    auto layouts = bl.GetLayout();
    unsigned int offset = 0;
    for(int i = 0; i < layouts.size(); i++){
        GLCall(glVertexAttribPointer(i, layouts[i].count, layouts[i].type, layouts[i].normalized ? GL_TRUE : GL_FALSE, bl.GetStride(), (const void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += layouts[i].size;
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(id));
}

void VertexArray::UnBind() const
{
    GLCall(glBindVertexArray(0));
}
