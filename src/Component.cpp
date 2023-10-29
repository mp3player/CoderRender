#include <component/Component.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


Component::Component( std::string name )
    : name( name )
{}

void Component::setNode( Node * node ){
    this->node = node;

}

Node * Component::getNode() const {
    return this->node;
}

std::string Component::getName() const {
    return this->name;
}

bool Component::isUpdated(){
    return !this->needUpdate;
}





// Transform
TransformComponent::TransformComponent( std::string name )
    : Component( name )
{}

void TransformComponent::setTranslation( glm::vec3 translation ){
    this->v3Translation = translation;
    this->needUpdate = true;
}

void TransformComponent::setScale( glm::vec3 scale ){
    this->v3Scale = scale;
    this->needUpdate = true;
}

void TransformComponent::setRotation( glm::vec3 rotation ){
    this->v3Rotation = rotation;
    this->needUpdate = true;
}

void TransformComponent::translate( float x , float y , float z ){
    this->v3Translation += glm::vec3( x , y , z );
    this->needUpdate = true;
}

void TransformComponent::rotate( float x , float y , float z ){
    this->v3Rotation += glm::vec3( x , y , z );
    this->needUpdate = true;
}

void TransformComponent::scale( float x , float y , float z ){
    this->v3Scale *= glm::vec3( x , y , z );
    this->needUpdate = true;
}

glm::mat4 TransformComponent::getTransformMatrix(){
    
    return this->transform;

}

void TransformComponent::init(){

}

void TransformComponent::update( float deltaTime ){

    if( this->needUpdate ){
        glm::translate( glm::mat4( 1.0f ) , this->v3Translation )
        * glm::toMat4( glm::quat( this->v3Rotation ) )
        * glm::scale( glm::mat4( 1.0f ) , this->v3Scale );
    }
    
}





// Mesh
MeshComponent::MeshComponent( Mesh * mesh , std::string name )
    : mesh( mesh ) , Component( name )
{}

MeshComponent::~MeshComponent(){
    delete mesh;
}

void MeshComponent::init(){

}

void MeshComponent::update( float deltaTime ){
    
}