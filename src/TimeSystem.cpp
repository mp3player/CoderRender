#include <system/TimeSystem.hpp>

const float F_CLOCKS_PER_SEC = float( CLOCKS_PER_SEC );

TimeSystem::TimeSystem( Scene * scene )
    : System( scene ) , currentTime( 0.0f ) , startTime( clock() )
{
    this->name = "time";
}

void TimeSystem::init() {
    
}

void TimeSystem::update( float deltaTime ){
    this->currentTime = clock() / F_CLOCKS_PER_SEC;
}

float TimeSystem::getDeltaTime(){
    
    float time = this->getCurrentTime();
    float deltaTime = ( time - this->currentTime ) / F_CLOCKS_PER_SEC;
    this->currentTime = time;
    return deltaTime;

}

float TimeSystem::getCurrentTime(){
    
    return clock() / F_CLOCKS_PER_SEC;

}