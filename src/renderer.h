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

#include "type.h"
#include "gl.h"

class Renderer {
public:
    Renderer(const VertexArrayBuffer& vertex_array,
             const TextureBuffer& texture_buffer);
    
    ~Renderer();
    
    void Update(const TextureBuffer& texture_buffer);
    void Draw();
    
private:
    static void ReadFileToStr(std::string* dst, const std::string& path);
    
    static void CompileShader(GLuint* shader_handle,
                              const std::string& source);
    
    static void LinkShader(GLuint* program_handle,
                           GLuint vert_shader_handle,
                           GLuint frag_shader_handle);
    
    static void LoadShader(const std::string& name,
                           GLuint* vert_shader_handle,
                           GLuint* frag_shader_handle,
                           GLuint* shader_program_handle);
    
private:
    // noncopyable
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
    
private:
    VertexArrayBuffer vertex_array_;
    
    GLuint vertex_array_handle_;
    GLuint vertex_buffer_handle_;
    
    GLuint model_vert_shader_handle_;
    GLuint model_frag_shader_handle_;
    GLuint model_shader_program_handle_;
    
    GLuint draw_buffer_vertex_array_handle_;
    GLuint draw_buffer_vertex_buffer_handle_;
    
    GLuint draw_buffer_vert_shader_handle_;
    GLuint draw_buffer_frag_shader_handle_;
    GLuint draw_buffer_shader_program_handle_;
    
    GLuint frame_buffer_texture_handle_;
    GLuint frame_buffer_handle_;
    GLuint render_buffer_handle_;
    
    GLsizei state_texture_size_;
    GLuint state_texture_handle_;
    
};