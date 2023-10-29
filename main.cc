
#include <string>
#include <Application.hpp>
#include <core/Ref.hpp>


int main()
{

    
    Application * application = Application::getInstance();
    application->run();

    Application::release();

    
    return 0;
}