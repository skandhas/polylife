#include "app.h"
#include "consts.h"
#include "model.h"
#include "renderer.h"
#include "controller.h"

#include <GL/glfw.h>

/* public */ App::App()
{
    
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
    
    if(!glfwOpenWindow(Consts::SCREEN_WIDTH,
                       Consts::SCREEN_HEIGHT,
                       Consts::RED_BITS,
                       Consts::GREEN_BITS,
                       Consts::BLUE_BITS,
                       Consts::ALPHA_BITS,
                       Consts::DEPTH_BITS,
                       Consts::STENCIL_BITS,
                       GLFW_WINDOW
                       ))
    {
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    glfwSetWindowTitle(Consts::APP_TITLE);
    glfwEnable(GLFW_STICKY_KEYS);
    
    glBindFragDataLocation.preload();
    glDeleteVertexArrays.preload();
    
    this->SetupOpenGL();
    this->MainLoop();
    
    glfwTerminate();
    
    return EXIT_SUCCESS;
}


/* public */ void App::SetupOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}


/* public */ void App::MainLoop()
{
    Model model(App::executable_path() + "../Resources/model.stl");
    Controller controller(model.connecting_face_buffer());
    Renderer renderer(model.vertex_array(), controller.texture_buffer());
    
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
