#include <Window.hpp>
#include <unordered_map>
#include <scene/Texture.hpp>
#include <core/Log.hpp>

Window::Window(unsigned int width , unsigned int height , const std::string title) : width(width) , height(height) , title(title) {
    this->init();
}

Window::~Window(){
    
    this->destory();
}

void Window::init(unsigned int width , unsigned int height , const std::string title ){
    this->width = width;
    this->height = height;
    this->title = title;
    if(this->window != NULL){
        this->destory();
    }
    this->init();
}

void Window::init(){
    if (!glfwInit()) {
        Log::cout( __FILE__ , "glfw init failed" );;
        this->visiable = false;
        return ;
    }
    this->window = glfwCreateWindow(this->width , this->height , this->title.c_str() , NULL,NULL);

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    if (this->window == NULL) {
        Log::cout( __FILE__ , "init window failed " );
        glfwTerminate();
        this->visiable = false;
        return ;
    }

    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::cout( __FILE__ , "Failed to initialize GLAD" );
        this->visiable = false;
        return ;
    }

    Log::cout( __FILE__, "window inited" );
}

void Window::destory(){
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

unsigned int Window::getWidth(){
    return this->width;
}

unsigned int Window::getHeight(){
    return this->height;
}

void Window::setWidth(unsigned int width){
    this->width = width;
}

void Window::setHeight(unsigned int height){
    this->height = height;
}

void Window::pollEvent(){
    glfwPollEvents();
}

void Window::swapBuffer(){
    glfwSwapBuffers(window);
}

bool Window::shouldClose(){
    return glfwWindowShouldClose(window);
}

void Window::close(){
    glfwSetWindowShouldClose( this->window , 1 );
}
