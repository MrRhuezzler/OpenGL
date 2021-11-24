#include "bufferLayout.h"

BufferLayout::BufferLayout() 
:stride(0)
{
    layouts = std::vector<Layout>();
}

BufferLayout::~BufferLayout() 
{}

unsigned int BufferLayout::GetStride() const
{
    return stride;
}

const std::vector<Layout>& BufferLayout::GetLayout() const
{
    return layouts;
}


template<typename T>
void BufferLayout::Add(unsigned int count, bool normalize) 
{
    std::cout << "Invalid Type" << std::endl;
    assert(false);
}

template<>
void BufferLayout::Add<float>(unsigned int count, bool normalize)
{
    Layout l = {GL_FLOAT, count, count * sizeof(float), normalize};
    layouts.push_back(l);
    stride += count * sizeof(float);
}

template<>
void BufferLayout::Add<unsigned int>(unsigned int count, bool normalize)
{
    Layout l = {GL_UNSIGNED_INT, count, count * sizeof(unsigned int), normalize};
    layouts.push_back(l);
    stride += count * sizeof(unsigned int);
}

template<>
void BufferLayout::Add<unsigned char>(unsigned int count, bool normalize)
{
    Layout l = {GL_UNSIGNED_BYTE, count, count * sizeof(unsigned char), normalize};
    layouts.push_back(l);
    stride += count * sizeof(unsigned char);
}
