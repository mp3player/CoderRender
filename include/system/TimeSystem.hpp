#ifndef _SYSTEM_TIME_HPP_
#define _SYSTEM_TIME_HPP_

#include <system/System.hpp>
#include <ctime>

struct TimeSystem : System {

    public:
        float tick;

    public:
        explicit TimeSystem( Scene * scene );

    public:

        void init();

        void update( float deltaTime ) ;

        float getDeltaTime();

};

#endif