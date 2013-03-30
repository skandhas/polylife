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

class Model;
class Renderer;

class App {
public:
    App();
    ~App();
    int Run();
    void LoadConfigure(const std::string& path);
    
    static void set_executable_path(const std::string& path);
    static const std::string& executable_path();
    
private:
    void SetupOpenGL();
    void MainLoop();
    
    struct {
        int screen_width_;
        int screen_height_;
        bool window_mode_;
		int reset_generation_;
    } config;
    
private:
    // noncopyable
    App(const App&);
    App& operator=(const App&);
    
private:
    static std::string executable_path_;
    
};