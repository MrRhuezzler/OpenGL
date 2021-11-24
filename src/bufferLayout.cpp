#include "bufferLayout.h"

BufferLayout::BufferLayout() 
:stride(0)
{}

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
