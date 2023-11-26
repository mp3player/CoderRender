
#include <string>
#include <Application.hpp>
#include <core/Log.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <scene/Screen.hpp>
#include <opengl/shader/ShaderPreProcessor.hpp>
#include <core/io/IO.hpp>
#include <component/Transform.hpp>

template< int a >
void fn(){
    std::cout << a << std::endl;
}

int main()
{


    Application * application = Application::getInstance();
    application->run();

    Application::release();


    
    return 0;
}