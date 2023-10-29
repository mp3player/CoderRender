#include <system/RenderSystem.hpp>
#include <iostream>
#include <opengl/shader/Program.hpp>

const std::string vertexFile = "/home/coder/project/c++/engine/shader/basic/vertex.vert";
const std::string fragmentFile = "/home/coder/project/c++/engine/shader/basic/fragment.frag";

static Program * program = Program::FromFile( vertexFile , fragmentFile );

RenderSystem::RenderSystem( Scene * scene , std::string name )
    : System( scene , name )
{

}

RenderSystem::~RenderSystem(){
    delete program;
}


void RenderSystem::init(){
    
}

void RenderSystem::update( float deltaTime ){
    if( !program->isReady ){
        bool ready = program->compile();
        if( !ready ){
            std::cout << "error" << std::endl;
            return ;
        }
    }
    System::createBuffer();
    for( Node * node : this->buffer ){
        if( node->hasComponent( "render" ) ){

            RenderComponent * renderComponent = ( RenderComponent* ) node->findComponent( "render" );
            TransformComponent * transformComponent = ( TransformComponent * ) node->findComponent( "transform" );
            
            
            
            // std::cout << "render" << std::endl;
        }
    }
}