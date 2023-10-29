#include <system/TimeSystem.hpp>

const float F_CLOCKS_PER_SEC = float( CLOCKS_PER_SEC );

TimeSystem::TimeSystem( Scene * scene , std::string name )
    : System( scene , name )
{

}

void TimeSystem::init() {
    this->tick = clock();
}

void TimeSystem::update( float deltaTime ){
    
}

float TimeSystem::getDeltaTime(){
    
    float currentTime = clock();
    float deltaTime = ( currentTime - this->tick ) / F_CLOCKS_PER_SEC;
    this->tick = currentTime;
    return deltaTime;

}