#include <component/Transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


// Transform
Transform::Transform( )
    : Component()
{
    this->name = "transform";
    this->needUpdate = true;
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

void Transform::setWorldTransform( glm::mat4 worldMatrix , glm::mat4 inverseWorldMatrix ){
    
    this->m4WorldMatrix = worldMatrix ;
    this->m4InverseWorldMatrix = inverseWorldMatrix;
    this->needUpdate = true;

}

void Transform::updateModelTransform(){

    this->m4ModelMatrix = glm::translate( glm::mat4( 1.0f ) , this->v3Translation )
        * glm::toMat4( glm::quat( this->v3Rotation ) )
        * glm::scale( glm::mat4( 1.0f ) , this->v3Scale );
    
    this->m4InverseModelMatrix = glm::inverse( this->m4ModelMatrix );

    this->m3NormalMatrix = glm::mat3( glm::transpose( m4InverseModelMatrix ) );

}

void Transform::updateViewTransform(){

    glm::mat3 transform( this->m4ModelMatrix );
    glm::vec3 eye = this->v3Translation;
    glm::vec3 center = this->v3Translation - transform * Z;

    this->v3LookAt = center;

    this->v3Up = glm::normalize( transform * Y ); 

    this->m4ViewMatrix = glm::lookAt( eye , center , this->v3Up );

    this->m4InverseViewMatrix = glm::inverse( this->m4ViewMatrix );

}

void Transform::updateModelWorldTransform(){

    this->m4ModelWorldMatrix = this->m4WorldMatrix * this->m4ModelMatrix;
    this->m4InverseModelWorldMatrix = this->m4InverseModelMatrix * this->m4InverseWorldMatrix;

    this->m3NormalWorldMatrix = glm::mat3( glm::transpose( this->m4InverseModelWorldMatrix ) );

}

void Transform::init(){

}

void Transform::update( float deltaTime ){

    if( !this->needUpdate )
        return ;

    // update modelMatrix 
    this->updateModelTransform();

    // update worldMatrix
    this->updateModelWorldTransform();

    // update viewMatrix;
    this->updateViewTransform();

    // update transform of children
    if( this->node != nullptr ){
        for( Node * node : this->node->children ){
            Transform * transform = node->getComponent<Transform>();
            if( transform == nullptr ) continue;
            transform->setWorldTransform( this->m4ModelWorldMatrix , this->m4InverseModelWorldMatrix );
        }
    }
    
    this->needUpdate = false;

    
}

