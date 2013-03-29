#pragma once

#include <GL/glfw.h>

class Controller {
public:
    typedef std::vector<unsigned char> TextureBuffer;
    typedef std::vector<std::unordered_set<size_t>> ConnectingFaceSetBuffer;
    
public:
    Controller(const ConnectingFaceSetBuffer& connecting_face_buffer);
    ~Controller();
    
    /* Thread-safe */ const TextureBuffer& texture_buffer() const;
    
private:
    /* Thread-safe */ bool thread_running() const;
    /* Thread-safe */ void set_thread_running(bool thread_running);
    
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
    
private:
    class MutexScope {
    public:
        MutexScope(GLFWmutex mutex);
        ~MutexScope();
    private:
        GLFWmutex mutex_;
        
    };
    
};