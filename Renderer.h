#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()





void GLDebugCallback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int severity,
    int length,
    const char* message,
    const void* userParam);



void GLFWErrorCallback(int error, const char* description);



