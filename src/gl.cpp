/*
 
 Copyright (c) 2013 h2so5 <mail@h2so5.net>
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 
 */

#include "gl.h"

GLExtensionFunc<void, GLsizei, GLuint *>
glGenVertexArrays("glGenVertexArrays");
    
GLExtensionFunc<void, GLuint>
glBindVertexArray("glBindVertexArray");
    
GLExtensionFunc<void, GLuint, GLuint, const char *>
glBindFragDataLocation("glBindFragDataLocation");

GLExtensionFunc<void, GLsizei, const GLuint *>
glDeleteVertexArrays("glDeleteVertexArrays");

GLExtensionFunc<void, GLuint, GLuint, GLuint>
glUniformBlockBinding("glUniformBlockBinding");

GLExtensionFunc<GLuint, GLuint, const GLchar *>
glGetUniformBlockIndex("glGetUniformBlockIndex");

#ifdef _WIN32
GLExtensionFunc<void, GLuint, GLsizei, const GLchar **, const GLint *>
glShaderSource("glShaderSource");
    
GLExtensionFunc<void, GLsizei, GLuint *>
glGenBuffers("glGenBuffers");

GLExtensionFunc<GLuint>
glCreateProgram("glCreateProgram");

GLExtensionFunc<void, GLuint, GLuint>
glAttachShader("glAttachShader");

GLExtensionFunc<void, GLuint, GLuint, const GLchar *>
glBindAttribLocation("glBindAttribLocation");

GLExtensionFunc<void, GLuint>
glLinkProgram("glLinkProgram");

GLExtensionFunc<void, GLuint, GLenum, GLint *>
glGetProgramiv("glGetProgramiv");

GLExtensionFunc<void, GLuint>
glUseProgram("glUseProgram");

GLExtensionFunc<void, GLenum, GLuint>
glBindBuffer("glBindBuffer");

GLExtensionFunc<void, GLenum, GLsizeiptr, const GLvoid *, GLenum>
glBufferData("glBufferData");

GLExtensionFunc<void, GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *>
glVertexAttribPointer("glVertexAttribPointer");

GLExtensionFunc<void, GLuint>
glEnableVertexAttribArray("glEnableVertexAttribArray");

GLExtensionFunc<void, GLuint>
glDeleteShader("glDeleteShader");

GLExtensionFunc<GLuint, GLenum>
glCreateShader("glCreateShader");

GLExtensionFunc<void, GLuint>
glCompileShader("glCompileShader");

GLExtensionFunc<void, GLuint, GLsizei, GLsizei *, GLchar *>
glGetShaderInfoLog("glGetShaderInfoLog");

GLExtensionFunc<void, GLuint, GLenum, GLint *>
glGetShaderiv("glGetShaderiv");
    
GLExtensionFunc<void, GLenum, GLuint>
glBindFramebuffer("glBindFramebuffer");
    
GLExtensionFunc<void, GLsizei, GLuint *>
glGenFramebuffers("glGenFramebuffers");

GLExtensionFunc<void, GLenum, GLenum, GLenum, GLuint, GLint>
glFramebufferTexture2D("glFramebufferTexture2D");

GLExtensionFunc<void, GLsizei, const GLuint *>
glDeleteBuffers("glDeleteBuffers");

GLExtensionFunc<void, GLuint>
glDeleteProgram("glDeleteProgram");

GLExtensionFunc<void, GLuint, GLsizei, GLsizei *, GLchar *>
glGetProgramInfoLog("glGetProgramInfoLog");

GLExtensionFunc<GLint, GLuint, const GLchar *>
glGetUniformLocation("glGetUniformLocation");

GLExtensionFunc<void, GLsizei, GLuint *>
glGenRenderbuffers("glGenRenderbuffers");

GLExtensionFunc<void, GLenum, GLuint>
glBindRenderbuffer("glBindRenderbuffer");

GLExtensionFunc<void, GLenum, GLenum, GLsizei, GLsizei>
glRenderbufferStorage("glRenderbufferStorage");

GLExtensionFunc<void, GLsizei, GLuint *>
glDeleteFramebuffers("glDeleteFramebuffers");

GLExtensionFunc<void, GLsizei, GLuint *>
glDeleteRenderbuffers("glDeleteRenderbuffers");

GLExtensionFunc<void, GLenum, GLenum, GLenum, GLuint>
glFramebufferRenderbuffer("glFramebufferRenderbuffer");

GLExtensionFunc<void, GLint, GLint>
glUniform1i("glUniform1i");

GLExtensionFunc<void, GLint, GLint, GLint>
glUniform2i("glUniform2i");

GLExtensionFunc<void, GLint, GLint, GLint, GLint>
glUniform3i("glUniform3i");

GLExtensionFunc<void, GLint, GLint, GLint, GLint, GLint>
glUniform4i("glUniform4i");

GLExtensionFunc<void, GLint, GLfloat>
glUniform1f("glUniform1f");

GLExtensionFunc<void, GLint, GLfloat, GLfloat>
glUniform2f("glUniform2f");

GLExtensionFunc<void, GLint, GLfloat, GLfloat, GLfloat>
glUniform3f("glUniform3f");

GLExtensionFunc<void, GLint, GLfloat, GLfloat, GLfloat, GLfloat>
glUniform4f("glUniform4f");

GLExtensionFunc<void, GLenum>
glActiveTexture("glActiveTexture");

GLExtensionFunc<void, GLint, GLsizei, GLboolean, GLfloat *>
glUniformMatrix4fv("glUniformMatrix4fv");

#endif
