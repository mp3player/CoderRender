#include <component/Component.hpp>

#include <core/Log.hpp>



Component::Component( )
    : name( "component" ) , needUpdate( true )
{}

Component::~Component(){
    
}

void Component::setNode( Node * node ){
    this->node = node;

}

Node * Component::getNode() const {
    return this->node;
}

std::string Component::getName() const {
    return this->name;
}

void Component::update(){
    this->update( 0.0f );
}

bool Component::isUpdated(){
    return !this->needUpdate;
}





// Mesh
MeshComponent::MeshComponent( Mesh * mesh )
    : mesh( mesh ) 
{
    this->name = "mesh";
}

MeshComponent::~MeshComponent(){
    
    delete mesh;
}

unsigned int MeshComponent::vertexCount() const {
    
    if( this->mesh == nullptr ) return 0;

    return this->mesh->vertexCount();

}

void MeshComponent::init(){

}

void MeshComponent::update( float deltaTime ){
    
}

// Material

RenderComponent::RenderComponent( ){
    this->name = "render";
}

RenderComponent::~RenderComponent(){
    delete this->material;
}

void RenderComponent::init (){

}

void RenderComponent::update( float deltaTime ){

}