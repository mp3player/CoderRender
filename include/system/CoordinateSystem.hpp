#ifndef _SYSTEM_COORDINATE_HPP_
#define _SYSTEM_COORDINATE_HPP_

#include <system/System.hpp>
#include <scene/Scene.hpp>

struct CoordinateSystem : System {

    private:
        Scene * scene ;

    public:
        explicit CoordinateSystem( Scene * scene );
    
    public :

        void init();
    
        void update( float deltaTime ) ;

};


#endif