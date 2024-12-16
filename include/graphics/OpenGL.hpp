#pragma once

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// OpenGL function declarations
extern "C" {
    extern const GLubyte* glGetString(GLenum name);
}
