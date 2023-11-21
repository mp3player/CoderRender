#include <system/RenderSystem.hpp>
#include <iostream>
#include <core/Log.hpp>
#include <component/Camera.hpp>
#include <component/Transform.hpp>
#include <opengl/shader/OpenGLProgram.hpp>



RenderSystem::RenderSystem( Scene * scene )
    : System( scene )
{
    this->name = "render";
    this->renderer = new OpenGLRenderer();
}

RenderSystem::~RenderSystem(){

    delete renderer;

}



void RenderSystem::init(){
    
}

void RenderSystem::update( float deltaTime ){

    scene->update( deltaTime );

    std::vector< Node * > objects = scene->findChildrenWithComponent< Transform >();
    
    for( Node * object : objects ){
        object->update( deltaTime );
    }

    Node * camera = scene->findChildWithComponent< Camera >();
    std::vector< Node * > nodes = scene->findChildrenWithComponent< RenderComponent >();
    std::vector< Node * > ambientLights = scene->findChildrenWithComponent< AmbientLight >();
    std::vector< Node * > directionalLights = scene->findChildrenWithComponent< DirectionalLight >();

    this->renderer->clear();
    this->renderer->render( this->scene );



}

