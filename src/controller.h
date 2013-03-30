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

#include <GL/glfw.h>

class Controller {
public:
    typedef std::vector<unsigned char> TextureBuffer;
    typedef std::vector<std::unordered_set<size_t>> ConnectingFaceSetBuffer;
    
public:
    Controller(const ConnectingFaceSetBuffer& connecting_face_buffer, int reset_generation);
    ~Controller();
    
    /* Thread-safe */ const TextureBuffer& texture_buffer() const;
    
private:
    /* Thread-safe */ bool thread_running() const;
    /* Thread-safe */ void set_thread_running(bool thread_running);

	void Reset();
    static void GLFWCALL CalcThread(void *void_self);
    
private:
    // noncopyable
    Controller(const Controller&);
    Controller& operator=(const Controller&);
    
private:
    ConnectingFaceSetBuffer connecting_face_buffer_;
    TextureBuffer texture_buffer_a_;
    TextureBuffer texture_buffer_b_;
    
    TextureBuffer* current_texture_buffer_;
    TextureBuffer* next_texture_buffer_;
    
    bool thread_running_;
    
    GLFWthread thread_;
    GLFWmutex mutex_;

	int reset_generation_;
	int generation_count_;
    
private:
    class MutexScope {
    public:
        MutexScope(GLFWmutex mutex);
        ~MutexScope();
    private:
        GLFWmutex mutex_;
        
    };
    
};