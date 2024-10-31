#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <iostream>

 void Renderer::GLDebugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
{
    const char* severityString = " ";
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severityString = "[NOTIFICATION]";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        severityString = "[LOW]";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        severityString = "[MEDIUM]";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        severityString = "[HIGH]";
        break;
    default:
        severityString = "[DEBUG]";
    }
    std::cout << "[OpenGL] " << message << "\n";
    if (severity > GL_DEBUG_SEVERITY_MEDIUM)
        __debugbreak();
}

 void Renderer::GLFWErrorCallback(int error, const char* description)
{
	std::cerr << description << "/n";
}

const void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
