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

#include "app.h"
#include "consts.h"
#include "model.h"
#include "renderer.h"
#include "controller.h"

#include <GL/glfw.h>

/* public */ App::App()
{
    this->config.screen_width_ = Consts::DEFAULT_SCREEN_WIDTH;
    this->config.screen_height_ = Consts::DEFAULT_SCREEN_HEIGHT;
    this->config.window_mode_ = true;
}


/* public */ App::~App()
{
    
}


/* public */ int App::Run()
{
    
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "GLFW initialize failed" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cerr << "GLFW successfully initialized" << std::endl;
    }
    
    // OpenGL profile
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    
    if(!glfwOpenWindow(config.screen_width_,
                       config.screen_height_,
                       Consts::RED_BITS,
                       Consts::GREEN_BITS,
                       Consts::BLUE_BITS,
                       Consts::ALPHA_BITS,
                       Consts::DEPTH_BITS,
                       Consts::STENCIL_BITS,
                       config.window_mode_ ? GLFW_WINDOW : GLFW_FULLSCREEN
                       ))
    {
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    glfwSetWindowTitle(Consts::APP_TITLE);
    glfwEnable(GLFW_STICKY_KEYS);
    
    glBindFragDataLocation.preload();
	glDeleteVertexArrays.preload();
    
#ifdef _WIN32
    glDeleteBuffers.preload();
    glDeleteProgram.preload();
	glDeleteFramebuffers.preload();
    glDeleteRenderbuffers.preload();
	glDeleteShader.preload();
#endif
    
    this->SetupOpenGL();
    this->MainLoop();
    
    glfwTerminate();
    
    return EXIT_SUCCESS;
}


/* public */ void App::LoadConfigure(const std::string& path)
{
    using namespace boost::property_tree;
    
    ptree pt;
    
    try {
        json_parser::read_json(path, pt);
    } catch (const std::exception e) {
        std::cout << e.what() << std::endl;
        std::cout << "Cannot load JSON configure; Use default." << std::endl;
    }
    
    this->config.screen_width_ = pt.get<int>("screen.width", Consts::DEFAULT_SCREEN_WIDTH);
    this->config.screen_height_ = pt.get<int>("screen.height", Consts::DEFAULT_SCREEN_HEIGHT);
    this->config.window_mode_ = pt.get<bool>("window_mode", true);
}


/* private */ void App::SetupOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}


/* private */ void App::MainLoop()
{
    Model model(App::executable_path() + "../Resources/model.stl");
    Controller controller(model.connecting_face_buffer());
    Renderer renderer(model.vertex_array(),
                      controller.texture_buffer(),
                      this->config.screen_width_,
                      this->config.screen_height_);
    
    while (glfwGetWindowParam(GLFW_OPENED))
    {
        renderer.Update(controller.texture_buffer());
        renderer.Draw();
        glfwSwapBuffers();
    }
}


/* static public */ void App::set_executable_path(const std::string& path)
{
    executable_path_ = path;
    size_t found_index;
    if ((found_index = executable_path_.find_last_of('/')) != std::string::npos)
    {
        executable_path_.resize(found_index);
        executable_path_ += '/';
    }
}


/* static public */ const std::string& App::executable_path()
{
    return executable_path_;
}


/* static private */ std::string App::executable_path_;

