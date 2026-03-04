#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if ((!x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())


void GLClearError();
bool GLLogCall();
