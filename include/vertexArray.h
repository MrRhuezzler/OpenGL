#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "vertexbuffer.h"
#include "bufferLayout.h"

class BufferLayout;

class VertexArray {

    unsigned int id;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const BufferLayout& bl);

        void Bind() const;
        void UnBind() const;

};

#endif // __VERTEXARRAY_H__