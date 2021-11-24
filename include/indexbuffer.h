#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

class IndexBuffer {

    unsigned int id;

    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;

};


#endif // __INDEXBUFFER_H__