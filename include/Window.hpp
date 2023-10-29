#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <scene/Scene.hpp>

class Window{
public:
    unsigned int width;
    unsigned int height;

    bool visiable = false;

    std::string title ;
    GLFWwindow * window;

public:
    Window() = default;
    Window(unsigned int , unsigned int , const std::string );
    ~Window();
    
public:
    void init(unsigned int , unsigned int , const std::string = "default" );
    void init();

    void destory();
    
    unsigned int getWidth();
    unsigned int getHeight();

    void setWidth(unsigned int);
    void setHeight(unsigned int);

public:
    void beforeDestroy();
    void beforeRender();

public: 

    void pollEvent();
    void swapBuffer();
    bool shouldClose();
    void close();

};

#endif