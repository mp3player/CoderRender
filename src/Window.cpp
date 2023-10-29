#include <Window.hpp>
#include <unordered_map>
#include <scene/Texture.hpp>

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
        std::cout << "glfw init failed" << std::endl;
        this->visiable = false;
        return ;
    }
    this->window = glfwCreateWindow(this->width , this->height , this->title.c_str() , NULL,NULL);

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    if (this->window == NULL) {
        std::cout << "init window failed " << std::endl;
        glfwTerminate();
        this->visiable = false;
        return ;
    }

    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        this->visiable = false;
        return ;
    }

    std::cout << "window inited" << std::endl;
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
