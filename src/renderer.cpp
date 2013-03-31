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

#include "renderer.h"
#include "app.h"
#include "consts.h"

/* public */ Renderer::Renderer(const VertexArrayBuffer& vertex_array,
                                const TextureBuffer& texture_buffer,
                                int screen_width,
                                int screen_height) :

screen_width_(screen_width),
screen_height_(screen_height),
vertex_array_(vertex_array)

{
    glGenVertexArrays(1, &this->vertex_array_handle_);
    glBindVertexArray(this->vertex_array_handle_);
    
    glGenBuffers(1, &this->vertex_buffer_handle_);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_handle_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * vertex_array.size(),
                 vertex_array.data(),
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (GLfloat*)0 + 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (GLfloat*)0 + 3);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    glGenVertexArrays(1, &this->draw_buffer_vertex_array_handle_);
    glBindVertexArray(this->draw_buffer_vertex_array_handle_);
    
    glGenBuffers(1, &this->draw_buffer_vertex_buffer_handle_);
    glBindBuffer(GL_ARRAY_BUFFER, this->draw_buffer_vertex_buffer_handle_);
    
    GLfloat dummy_array[6];
    glBufferData(GL_ARRAY_BUFFER, sizeof(dummy_array), dummy_array, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    glGenFramebuffers(1, &this->frame_buffer_handle_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_handle_);
    
    glGenRenderbuffers(1, &this->render_buffer_handle_);
    glBindRenderbuffer(GL_RENDERBUFFER, this->render_buffer_handle_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->screen_width_, this->screen_height_);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glGenTextures(1, &this->frame_buffer_texture_handle_);
    glBindTexture(GL_TEXTURE_2D, this->frame_buffer_texture_handle_);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 this->screen_width_, this->screen_height_,
                 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           this->frame_buffer_texture_handle_, 0);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER,
                              this->render_buffer_handle_);
    
    this->model_vert_shader_handle_ = glCreateShader(GL_VERTEX_SHADER);
    this->model_frag_shader_handle_ = glCreateShader(GL_FRAGMENT_SHADER);
    this->model_shader_program_handle_ = glCreateProgram();
    
    LoadShader("model",
               &this->model_vert_shader_handle_,
               &this->model_frag_shader_handle_,
               &this->model_shader_program_handle_);
    
    this->draw_buffer_vert_shader_handle_ = glCreateShader(GL_VERTEX_SHADER);
    this->draw_buffer_frag_shader_handle_ = glCreateShader(GL_FRAGMENT_SHADER);
    this->draw_buffer_shader_program_handle_ = glCreateProgram();
    
    LoadShader("draw_buffer",
               &this->draw_buffer_vert_shader_handle_,
               &this->draw_buffer_frag_shader_handle_,
               &this->draw_buffer_shader_program_handle_);
    
    glGenTextures(1, &state_texture_handle_);
    glBindTexture(GL_TEXTURE_2D, state_texture_handle_);
    
    this->state_texture_size_ = sqrt(static_cast<double>(texture_buffer.size()));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                 this->state_texture_size_, this->state_texture_size_,
                 0, GL_RED, GL_UNSIGNED_BYTE, texture_buffer.data());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    GLuint location = glGetUniformLocation(this->model_shader_program_handle_, "texture_size");
    glUseProgram(this->model_shader_program_handle_);
    glUniform1i(location, this->state_texture_size_);
    
    location = glGetUniformLocation(this->draw_buffer_shader_program_handle_, "screen");
    glUseProgram(this->draw_buffer_shader_program_handle_);
    glUniform2f(location,
                static_cast<GLfloat>(this->screen_width_),
                static_cast<GLfloat>(this->screen_height_));
}


/* public */ Renderer::~Renderer()
{
    glDeleteBuffers(1, &vertex_array_handle_);
    
    glDeleteProgram(this->model_shader_program_handle_);
    glDeleteShader(this->model_vert_shader_handle_);
    glDeleteShader(this->model_frag_shader_handle_);
    
    glDeleteProgram(this->draw_buffer_shader_program_handle_);
    glDeleteShader(this->draw_buffer_vert_shader_handle_);
    glDeleteShader(this->draw_buffer_frag_shader_handle_);
    
    glDeleteTextures(1, &state_texture_handle_);
    glDeleteVertexArrays(1, &this->vertex_array_handle_);
}


/* public */ void Renderer::Update(const TextureBuffer& texture_buffer)
{
    glBindTexture(GL_TEXTURE_2D, state_texture_handle_);
    
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                    this->state_texture_size_, this->state_texture_size_,
                    GL_RED, GL_UNSIGNED_BYTE, texture_buffer.data());
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    static int cnt = 0;
    cnt++;
    float angle = cnt / 5.0f;
    
    glm::mat4 mMatrix, vMatrix, pMatrix, mvpMatrix;
    
    mMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.8f));
    mMatrix = glm::rotate(mMatrix, angle, glm::vec3(0.0f, 1.0f, 1.0f));
    
    vMatrix = glm::lookAt(
                          glm::vec3(1.0f, 0.0f, 1.0f),
                          glm::vec3(0.1f, 0, 0),
                          glm::vec3(0, 1, 0));
    float aspect_ratio = 1.0 * this->screen_width_ / this->screen_height_;
    
    pMatrix = glm::perspective(60.0f, aspect_ratio, 0.05f, 10.0f);
    
    mvpMatrix = pMatrix * vMatrix * mMatrix;
    
    GLuint location = glGetUniformLocation(this->model_shader_program_handle_, "mvpMatrix");
    glUseProgram(this->model_shader_program_handle_);
    glUniformMatrix4fv(location, 1, false, &mvpMatrix[0][0]);
}


/* public */ void Renderer::Draw()
{
    glBlendFunc(GL_SRC_COLOR, GL_ONE);
    
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_handle_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindTexture(GL_TEXTURE_2D, this->state_texture_handle_);
    glBindVertexArray(this->vertex_array_handle_);
    glUseProgram(this->model_shader_program_handle_);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertex_array_.size()));
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, this->frame_buffer_texture_handle_);
    glBindVertexArray(this->draw_buffer_vertex_array_handle_);
    glUseProgram(this->draw_buffer_shader_program_handle_);
    
    GLuint location = glGetUniformLocation(this->draw_buffer_shader_program_handle_, "mode");
    glUniform1i(location, 0);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(6));
    glUniform1i(location, 1);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(6));
    
    glBindTexture(GL_TEXTURE_2D, 0);
}


/* static private */ void Renderer::ReadFileToStr(std::string* dst, const std::string& path)
{
    std::ifstream ifs(path.c_str());
    std::stringstream source;
    source << ifs.rdbuf();
    *dst = source.str();
}


/* static private */ void Renderer::CompileShader(GLuint* shader_handle,
                                                  const std::string& source)
{
    const char* source_ptr = source.c_str();
    
    glShaderSource(*shader_handle, 1, &source_ptr, nullptr);
    glCompileShader(*shader_handle);
    
    // Get compilaton status
    GLint status;
    glGetShaderiv(*shader_handle, GL_COMPILE_STATUS, &status);
    
    if (status != GL_TRUE)
    {
        // Get error message
        int length;
        glGetShaderiv(*shader_handle, GL_INFO_LOG_LENGTH, &length);
        
        std::unique_ptr<char[]> shader_log(new char[length]);
        glGetShaderInfoLog(*shader_handle, length, nullptr, shader_log.get());
        std::cerr << "[Shader complation error] " << shader_log.get() << std::endl;
    }
}


/* static private */ void Renderer::LinkShader(GLuint* program_handle,
                                               GLuint vert_shader_handle,
                                               GLuint frag_shader_handle)
{
    glAttachShader(*program_handle, vert_shader_handle);
    glAttachShader(*program_handle, frag_shader_handle);
    
    glBindAttribLocation(*program_handle, 0, "pv");
    glBindAttribLocation(*program_handle, 1, "cv");
    glBindFragDataLocation(*program_handle, 0, "fc");
    
    glLinkProgram(*program_handle);
    
    GLint status;
    glGetProgramiv(*program_handle, GL_LINK_STATUS, &status);
    
    // Compilaton failed
    if (status != GL_TRUE)
    {
        // Get error message
        int length;
        glGetProgramiv(*program_handle, GL_INFO_LOG_LENGTH, &length);
        
        std::unique_ptr<char[]> program_log(new char[length]);
        glGetProgramInfoLog(*program_handle, length, nullptr, program_log.get());
        std::cout << "[Shader link error] " << program_log.get() << std::endl;
    }
}


/* static private */ void Renderer::LoadShader(const std::string& name,
                                               GLuint* vert_shader_handle,
                                               GLuint* frag_shader_handle,
                                               GLuint* shader_program_handle)
{
    std::string vert_shader_source;
    std::string frag_shader_source;
    
    ReadFileToStr(&vert_shader_source, App::executable_path() + "../Resources/" + name + ".vert");
    ReadFileToStr(&frag_shader_source, App::executable_path() + "../Resources/" + name + ".frag");
    
    CompileShader(vert_shader_handle, vert_shader_source);
    CompileShader(frag_shader_handle, frag_shader_source);
    
    LinkShader(shader_program_handle,
               *vert_shader_handle,
               *frag_shader_handle);
}
