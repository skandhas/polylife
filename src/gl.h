#pragma once

#include "extension.h"

#ifdef __APPLE__
#define GL_UNIFORM_BUFFER GL_UNIFORM_BUFFER_EXT
#endif

#ifdef __APPLE__
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>
#endif

extern GLExtensionFunc<void, GLsizei, GLuint *>
glGenVertexArrays;

extern GLExtensionFunc<void, GLsizei, const GLuint *>
glDeleteVertexArrays;

extern GLExtensionFunc<void, GLuint, GLuint, const char *>
glBindFragDataLocation;

extern GLExtensionFunc<void, GLuint>
glBindVertexArray;