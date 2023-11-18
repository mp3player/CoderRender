#ifndef _SYSTEM_RENDER_HPP_
#define _SYSTEM_RENDER_HPP_

#include <system/System.hpp>

#include <opengl/shader/Program.hpp>
#include <core/Buffer.hpp>
#include <core/MemoryManager.hpp>
#include <component/Camera.hpp>
#include <component/Light.hpp>

#include <render/Renderer.hpp>






struct RenderSystem : System {

    private:

        Renderer * renderer;

    public:

        Node * mainCamera = nullptr ;
        std::vector< Node * > cameras;
        std::vector< Node * > nodes;
        std::vector< AmbientLight * > ambientLights;
        std::vector< DirectionalLight * > directionalLights;
        std::vector< SpotLight * > spotLights;

    public:

        RenderSystem( Scene * scene );
        ~RenderSystem();

    public:
    
        void init();

        void update( float deltaTime );

};

#endif