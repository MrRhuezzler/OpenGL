#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <cstdlib>

#define DEBUG

#define assert(x) if(!(x)) exit(10);

#ifdef DEBUG
#define GLCall(x) GLClearErrors();\
    x;\
    assert(GLLogError(#x, __FILE__, __LINE__))
#endif

#ifndef DEBUG
#define GLCall(x) x;
#endif

void GLClearErrors();
bool GLLogError(const char* function, const char* file, int line);

#endif // __RENDERER_H__