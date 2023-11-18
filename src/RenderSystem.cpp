#include <system/RenderSystem.hpp>
#include <iostream>

#include <core/Log.hpp>
#include <component/Camera.hpp>




RenderSystem::RenderSystem( Scene * scene )
    : System( scene )
{
    this->name = "render";
    this->renderer = new Renderer();
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


    this->renderer->render( scene );

}

