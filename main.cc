
#include <string>
#include <Application.hpp>
#include <core/Log.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <scene/Screen.hpp>


int main()
{


    Application * application = Application::getInstance();
    application->run();

    Application::release();


    
    return 0;
}