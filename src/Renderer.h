#pragma once

#include <GL/glew.h>


#define ASSERT(x) if (!(x)) __debugbreak()

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
    
public:
   static void GLDebugCallback(
        unsigned int source,
        unsigned int type,
        unsigned int id,
        unsigned int severity,
        int length,
        const char* message,
        const void* userParam);



  static void GLFWErrorCallback(int error, const char* description);

  const void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

  void Clear() const;



};







