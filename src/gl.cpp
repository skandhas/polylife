#include "gl.h"

GLExtensionFunc<void, GLsizei, GLuint *>
glGenVertexArrays("glGenVertexArrays");

GLExtensionFunc<void, GLsizei, const GLuint *>
glDeleteVertexArrays("glDeleteVertexArrays");

GLExtensionFunc<void, GLuint, GLuint, const char *>
glBindFragDataLocation("glBindFragDataLocation");

GLExtensionFunc<void, GLuint>
glBindVertexArray("glBindVertexArray");