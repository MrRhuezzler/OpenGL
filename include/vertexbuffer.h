#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

class VertexBuffer {

    unsigned int id;

    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void UnBind() const;

};


#endif // __VERTEXBUFFER_H__