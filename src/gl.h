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

#pragma once

#include "extension.h"

#ifdef __APPLE__
#define GL_UNIFORM_BUFFER GL_UNIFORM_BUFFER_EXT
#endif

#ifdef __APPLE__
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>
#endif

#ifdef _WINDOWS

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw.lib")

#define GL_ARRAY_BUFFER      0x8892
#define GL_STATIC_DRAW       0x88E4
#define GL_VERTEX_SHADER     0x8B31
#define GL_FRAGMENT_SHADER   0x8B30
#define GL_LINK_STATUS       0x8B82
#define GL_COMPILE_STATUS    0x8B81
#define GL_INFO_LOG_LENGTH   0x8B84

#define GL_RENDERBUFFER      0x8D41
#define GL_FRAMEBUFFER       0x8D40
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT  0x8D00

#define GL_TEXTURE0          0x84C0
#define GL_TEXTURE1          0x84C1
#define GL_TEXTURE2          0x84C2
#define GL_TEXTURE3          0x84C3
#define GL_TEXTURE4          0x84C4
#define GL_TEXTURE5          0x84C5
#define GL_TEXTURE6          0x84C6
#define GL_TEXTURE7          0x84C7
#define GL_TEXTURE8          0x84C8
#define GL_TEXTURE9          0x84C9

	typedef char GLchar;
    typedef long GLsizeiptr;
    
#endif

extern GLExtensionFunc<void, GLsizei, GLuint *>
glGenVertexArrays;
    
extern GLExtensionFunc<void, GLuint>
glBindVertexArray;
    
extern GLExtensionFunc<void, GLuint, GLuint, const char *>
glBindFragDataLocation;

extern GLExtensionFunc<void, GLuint, GLuint, GLuint>
glUniformBlockBinding;

extern GLExtensionFunc<GLuint, GLuint, const GLchar *>
glGetUniformBlockIndex;

extern GLExtensionFunc<void, GLsizei, const GLuint *>
glDeleteVertexArrays;

#ifdef _WIN32
extern GLExtensionFunc<void, GLuint, GLsizei, const GLchar **, const GLint *>
glShaderSource;
    
extern GLExtensionFunc<void, GLsizei, GLuint *>
glGenBuffers;

extern GLExtensionFunc<GLuint>
glCreateProgram;

extern GLExtensionFunc<void, GLuint, GLuint>
glAttachShader;

extern GLExtensionFunc<void, GLuint, GLuint, const GLchar *>
glBindAttribLocation;

extern GLExtensionFunc<void, GLuint>
glLinkProgram;

extern GLExtensionFunc<void, GLuint, GLenum, GLint *>
glGetProgramiv;

extern GLExtensionFunc<void, GLuint>
glUseProgram;

extern GLExtensionFunc<void, GLenum, GLuint>
glBindBuffer;

extern GLExtensionFunc<void, GLenum, GLsizeiptr, const GLvoid *, GLenum>
glBufferData;

extern GLExtensionFunc<void, GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *>
glVertexAttribPointer;

extern GLExtensionFunc<void, GLuint>
glEnableVertexAttribArray;

extern GLExtensionFunc<void, GLuint>
glDeleteShader;

extern GLExtensionFunc<GLuint, GLenum>
glCreateShader;

extern GLExtensionFunc<void, GLuint>
glCompileShader;

extern GLExtensionFunc<void, GLuint, GLsizei, GLsizei *, GLchar *>
glGetShaderInfoLog;

extern GLExtensionFunc<void, GLuint, GLenum, GLint *>
glGetShaderiv;
    
extern GLExtensionFunc<void, GLenum, GLuint>
glBindFramebuffer;
    
extern GLExtensionFunc<void, GLsizei, GLuint *>
glGenFramebuffers;
    
extern GLExtensionFunc<void, GLenum, GLenum, GLenum, GLuint, GLint>
glFramebufferTexture2D;

extern GLExtensionFunc<void, GLsizei, const GLuint *>
glDeleteBuffers;

extern GLExtensionFunc<void, GLuint>
glDeleteProgram;

extern GLExtensionFunc<void, GLuint, GLsizei, GLsizei *, GLchar *>
glGetProgramInfoLog;

extern GLExtensionFunc<GLint, GLuint, const GLchar *>
glGetUniformLocation;

extern GLExtensionFunc<void, GLsizei, GLuint *>
glGenRenderbuffers;

extern GLExtensionFunc<void, GLenum, GLuint>
glBindRenderbuffer;

extern GLExtensionFunc<void, GLenum, GLenum, GLsizei, GLsizei>
glRenderbufferStorage;

extern GLExtensionFunc<void, GLsizei, GLuint *>
glDeleteFramebuffers;

extern GLExtensionFunc<void, GLsizei, GLuint *>
glDeleteRenderbuffers;

extern GLExtensionFunc<void, GLenum, GLenum, GLenum, GLuint>
glFramebufferRenderbuffer;

extern GLExtensionFunc<void, GLint, GLint>
glUniform1i;

extern GLExtensionFunc<void, GLint, GLint, GLint>
glUniform2i;

extern GLExtensionFunc<void, GLint, GLint, GLint, GLint>
glUniform3i;

extern GLExtensionFunc<void, GLint, GLint, GLint, GLint, GLint>
glUniform4i;

extern GLExtensionFunc<void, GLint, GLfloat>
glUniform1f;

extern GLExtensionFunc<void, GLint, GLfloat, GLfloat>
glUniform2f;

extern GLExtensionFunc<void, GLint, GLfloat, GLfloat, GLfloat>
glUniform3f;

extern GLExtensionFunc<void, GLint, GLfloat, GLfloat, GLfloat, GLfloat>
glUniform4f;

extern GLExtensionFunc<void, GLint, GLsizei, GLboolean, GLfloat *>
glUniformMatrix4fv;

extern GLExtensionFunc<void, GLenum>
glActiveTexture;

#endif
