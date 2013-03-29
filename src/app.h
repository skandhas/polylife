#pragma once

class Model;
class Renderer;

class App {
public:
    App();
    ~App();
    int Run();
    
    static void set_executable_path(const std::string& path);
    static const std::string& executable_path();
    
private:
    void SetupOpenGL();
    void MainLoop();
    
private:
    // noncopyable
    App(const App&);
    App& operator=(const App&);
    
private:
    static std::string executable_path_;
    
};