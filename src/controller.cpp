#include "controller.h"
#include "consts.h"

namespace {
size_t pow2(size_t in)
{
    size_t i;
    for (i = 1; i < in; i <<= 1);
    return i;
}
} // anonymous namespace

    
/* public */ Controller::Controller(const ConnectingFaceSetBuffer& connecting_face_buffer) :

connecting_face_buffer_(connecting_face_buffer),
thread_running_(false),
mutex_(glfwCreateMutex())

{
    size_t texture_size = pow2(sqrt(connecting_face_buffer.size()));
    this->texture_buffer_a_.resize(texture_size * texture_size);
    
    for (size_t i = 0; i < texture_size * texture_size; i++)
    {
        float rand_value = glm::simplex(glm::vec2(i % texture_size / 16.f, i / texture_size / 16.f));
        this->texture_buffer_a_[i] = (rand_value > 0.5) ? 1 : 0;
    }
    
    this->texture_buffer_b_ = this->texture_buffer_a_;
    this->current_texture_buffer_ = &this->texture_buffer_a_;
    this->next_texture_buffer_ = &this->texture_buffer_b_;
    
    set_thread_running(true);
    thread_ = glfwCreateThread(Controller::CalcThread, this);
}


/* public */ Controller::~Controller()
{
    set_thread_running(false);
    glfwWaitThread(thread_, GLFW_WAIT);
    
    glfwDestroyMutex(mutex_);
    glfwDestroyThread(thread_);
}


/* public */ const Controller::TextureBuffer& Controller::texture_buffer() const
{
    MutexScope mutex_scope(mutex_);
    return *this->current_texture_buffer_;
}


/* private */ bool Controller::thread_running() const
{
    MutexScope mutex_scope(mutex_);
    return thread_running_;
}


/* private */ void Controller::set_thread_running(bool thread_running)
{
    MutexScope mutex_scope(mutex_);
    thread_running_ = thread_running;
}


/* static private */ void GLFWCALL Controller::CalcThread(void *void_self)
{
    Controller* self = reinterpret_cast<Controller*>(void_self);
    
    while (self->thread_running()) {
        
        size_t face_size = self->connecting_face_buffer_.size();
        for (int i = 0; i < face_size; ++i)
        {
            bool alive = ((*self->current_texture_buffer_)[i] > 0);
            int around_alives = 0;
            
            const auto& face_set = self->connecting_face_buffer_[i];
            for (auto it = face_set.begin(); it != face_set.end(); ++it)
            {
                around_alives += ((*self->current_texture_buffer_)[*it] > 0) ? 1 : 0;
            }
            
            bool next_alive =
            (alive && (around_alives == 2 || around_alives == 3)) ||
            (!alive && around_alives == 3);
            
            if (alive && next_alive)
            {
                (*self->next_texture_buffer_)[i] = std::min(255, (*self->next_texture_buffer_)[i] + 1);
            }
            else
            {
                (*self->next_texture_buffer_)[i] = next_alive;
            }
        }
        
        {
            MutexScope mutex_scope(self->mutex_);
            std::swap(self->next_texture_buffer_, self->current_texture_buffer_);
        }
        
        usleep(Consts::THREAD_SLEEP_USEC);
    }
}


/* public */ Controller::MutexScope::MutexScope(GLFWmutex mutex) :

mutex_(mutex)

{
    glfwLockMutex(mutex_);
}


/* public */ Controller::MutexScope::~MutexScope()
{
    glfwUnlockMutex(mutex_);
}

