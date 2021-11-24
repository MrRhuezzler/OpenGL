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
        void Add(unsigned int count, bool normalize);

        unsigned int GetStride() const;
        const std::vector<Layout>& GetLayout() const;

};

// GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
// GLCall(glEnableVertexAttribArray(0));

#endif // __BUFFERLAYOUT_H__