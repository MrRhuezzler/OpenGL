#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include <string>

class Texture2D{

    int slot;
    unsigned int id;
    std::string filePath;
    int width, height, BPP;
    unsigned char* localBuffer;

    public:
        Texture2D(const std::string& path);
        ~Texture2D();

        // Bind texture to a slot, you can load many textures at the same time. (upto 32 in a desktop GPU and 8 in a android GPU)
        void Bind(unsigned int slot = 0) const;
        void UnBind() const;

};


#endif // __TEXTURE2D_H__