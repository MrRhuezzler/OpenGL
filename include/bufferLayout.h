#ifndef __BUFFERLAYOUT_H__
#define __BUFFERLAYOUT_H__

#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "renderer.h"

struct Layout
{
    unsigned int type;
    unsigned int count;
    unsigned int size;
    bool normalized;
};


class BufferLayout {

    std::vector<Layout> layouts;
    unsigned int stride;

    public:
        BufferLayout();
        ~BufferLayout();

        template<typename T>
        void Add(int count, bool normalize);

        unsigned int GetStride() const;
        const std::vector<Layout>& GetLayout() const;

};

template<typename T>
void BufferLayout::Add(int count, bool normalize) 
{
    std::cout << "Invalid Type" << std::endl;
    assert(false);
}

template<>
void BufferLayout::Add<float>(int count, bool normalize)
{
    Layout l = {GL_FLOAT, count, count * sizeof(float), normalize};
    layouts.push_back(l);
    stride += sizeof(float);
}

template<>
void BufferLayout::Add<unsigned int>(int count, bool normalize)
{
    Layout l = {GL_UNSIGNED_INT, count, count * sizeof(unsigned int), normalize};
    layouts.push_back(l);
    stride += sizeof(unsigned int);
}

template<>
void BufferLayout::Add<unsigned char>(int count, bool normalize)
{
    Layout l = {GL_UNSIGNED_BYTE, count, count * sizeof(unsigned char), normalize};
    layouts.push_back(l);
    stride += sizeof(unsigned char);
}


// GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
// GLCall(glEnableVertexAttribArray(0));

#endif // __BUFFERLAYOUT_H__