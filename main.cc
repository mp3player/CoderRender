
#include <string>
#include <Application.hpp>


int main()
{

    std::vector< unsigned int > vec;

    Application * application = Application::getInstance();
    
    application->init();
    application->run();

    Application::release();

    return 0;
}