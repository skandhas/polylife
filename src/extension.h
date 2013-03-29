#pragma once

#include<GL/glfw.h>

class GLExtensionFuncBase {
    
public:
    void preload()
    {
        getAddress();
    }
    
protected:
    GLExtensionFuncBase(const std::string& name) : func_ptr_(nullptr), name_(name) {}
    
    void* getAddress()
    {
        if (!func_ptr_)
        {
            func_ptr_ = glfwGetProcAddress(name_.c_str());
            
            if (!func_ptr_)
            {
                throw std::runtime_error("Cannot get a pointer of " + name_ + "()");
            }
        }
        
        return func_ptr_;
    }
    
private:
    std::string name_;
    void *func_ptr_;
    
};


template <class R, class A1 = void, class A2 = void, class A3 = void, class A4 = void, class A5 = void, class A6 = void>
class GLExtensionFunc : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() (A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6)
    {
        typedef R (APIENTRY * glExtensionFunc_t)(A1, A2, A3, A4, A5, A6);
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))(arg1, arg2, arg3, arg4, arg5, arg6);
    }
    
};


template <class R, class A1, class A2, class A3, class A4, class A5>
class GLExtensionFunc<R, A1, A2, A3, A4, A5> : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() (A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5)
    {
        typedef R (APIENTRY * glExtensionFunc_t)(A1, A2, A3, A4, A5);
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))(arg1, arg2, arg3, arg4, arg5);
    }
    
};


template <class R, class A1, class A2, class A3, class A4>
class GLExtensionFunc<R, A1, A2, A3, A4> : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() (A1 arg1, A2 arg2, A3 arg3, A4 arg4)
    {
        typedef R (APIENTRY * glExtensionFunc_t)(A1, A2, A3, A4);
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))(arg1, arg2, arg3, arg4);
    }
    
};


template <class R, class A1, class A2, class A3>
class GLExtensionFunc<R, A1, A2, A3> : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() (A1 arg1, A2 arg2, A3 arg3)
    {
        typedef R (APIENTRY * glExtensionFunc_t)(A1, A2, A3);
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))(arg1, arg2, arg3);
    }
    
};


template <class R, class A1, class A2>
class GLExtensionFunc<R, A1, A2> : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() (A1 arg1, A2 arg2)
    {
        typedef R (APIENTRY * glExtensionFunc_t)(A1, A2);
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))(arg1, arg2);
    }
    
};


template <class R, class A1>
class GLExtensionFunc<R, A1>  : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() (A1 arg1)
    {
        typedef R (APIENTRY * glExtensionFunc_t)(A1);
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))(arg1);
    }
    
};


template <class R>
class GLExtensionFunc<R> : public GLExtensionFuncBase {
    
public:
    GLExtensionFunc(const std::string& name) : GLExtensionFuncBase(name) {}
    
    R operator() ()
    {
        typedef R (APIENTRY * glExtensionFunc_t)();
        return (*reinterpret_cast<glExtensionFunc_t>(getAddress()))();
    }
    
};