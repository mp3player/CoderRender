#include <system/CoordinateSystem.hpp>
#include <iostream>

CoordinateSystem::CoordinateSystem( Scene * scene , std::string name )
    : System( scene , name )
{

}


void CoordinateSystem::init(){

}
    
void CoordinateSystem::update( float deltaTime ){
    System::createBuffer();


}