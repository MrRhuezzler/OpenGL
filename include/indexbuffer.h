#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

class IndexBuffer {

    unsigned int id;
    unsigned int count;

    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;
        unsigned int GetCount() const;

};


#endif // __INDEXBUFFER_H__