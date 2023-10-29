#ifndef _SYSTEM_RENDER_HPP_
#define _SYSTEM_RENDER_HPP_

#include <system/System.hpp>

struct RenderSystem : System {

    public:
        RenderSystem( Scene * scene , std::string name = "render");
        ~RenderSystem();

    public:
    
        void init();

        void update( float deltaTime );

};

#endif