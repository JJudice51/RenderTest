#include "Renderer.h"
#include <iostream>

void GLDebugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
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

void GLFWErrorCallback(int error, const char* description)
{
	std::cerr << description << "/n";
}
