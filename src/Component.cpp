#include <component/Component.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <core/Log.hpp>



Component::Component( )
    : name( "component" ) , needUpdate( true )
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

void Component::update(){
    this->update( 0.0f );
}

bool Component::isUpdated(){
    return !this->needUpdate;
}





// Transform
Transform::Transform( )
    : Component()
{
    this->name = "transform";
    this->updateTransform();
}

void Transform::setTranslation( glm::vec3 translation ){

    if( this->v3Translation == translation ) return ;
    this->v3Translation = translation;
    this->needUpdate = true;

}

void Transform::setScale( glm::vec3 scale ){

    if( this->v3Scale == scale ) return ;
    this->v3Scale = scale;
    this->needUpdate = true;

}

void Transform::setRotation( glm::vec3 rotation ){

    if( this->v3Rotation == rotation ) return ;
    this->v3Rotation = rotation;
    this->needUpdate = true;

}

void Transform::translate( float x , float y , float z ){
    
    if( x == 0 && y == 0 && z == 0 ) return ;

    this->v3Translation += glm::vec3( x , y , z );
    this->needUpdate = true;

}

void Transform::rotate( float x , float y , float z ){

    if( x == 0 && y == 0 && z == 0 ) return ;
    this->v3Rotation += glm::vec3( x , y , z );
    this->needUpdate = true;

}

void Transform::scale( float x , float y , float z ){

    if( x == 1 && y == 1 && z == 1 ) return ;
    
    this->v3Scale *= glm::vec3( x , y , z );
    this->needUpdate = true;
    
}

void Transform::setWorldTransform( glm::mat4 worldTransform , glm::mat4 inverseWorldTransform ){
    
    this->m4WorldTransform = worldTransform ;
    this->m4InverseWorldTransform = inverseWorldTransform;
    this->needUpdate = true;

}

void Transform::updateTransform(){

    this->m4ModelTransform = glm::translate( glm::mat4( 1.0f ) , this->v3Translation )
        * glm::toMat4( glm::quat( this->v3Rotation ) )
        * glm::scale( glm::mat4( 1.0f ) , this->v3Scale );
    
    this->m4InverseModelTransform = glm::inverse( this->m4ModelTransform );

    this->m3NormalMatrix = glm::mat3( glm::transpose( m4InverseModelTransform ) );

}

void Transform::updateModelWorldTransform(){

    this->m4ModelWorldTransform = this->m4WorldTransform * this->m4ModelTransform;
    this->m4InverseModelWorldTransform = this->m4InverseModelTransform * this->m4InverseWorldTransform;

    this->m3NormalWorldMatrix = glm::mat3( glm::transpose( this->m4InverseModelWorldTransform ) );

}

void Transform::init(){

}

void Transform::update( float deltaTime ){

    if( !this->needUpdate )
        return ;

    {
        // update up and right vector
        glm::mat3 m3RotMat = glm::mat3( glm::toMat4( glm::quat( this->v3Rotation ) ) );
        this->v3Up = m3RotMat * Y;
        this->v3Right = m3RotMat * X;
        this->v3LookAt = glm::cross( this->v3Right , this->v3Up );

        // update modelMatrix and viewMatrix( inverseModelMatrix )
        this->updateTransform();

        // update worldMatrix
        this->updateModelWorldTransform();

        // update children
        for( Node * node : this->node->children ){
            Transform * transform = node->getComponent<Transform>();
            if( transform == nullptr ) continue;
            transform->setWorldTransform( this->m4ModelWorldTransform , this->m4InverseModelWorldTransform );
        }

        this->needUpdate = false;

    }
    
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