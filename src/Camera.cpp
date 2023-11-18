#include <component/Camera.hpp>
#include <glm/ext.hpp>




// Camera

Camera::Camera( )
{
    this->name = "camera";
}

Camera::~Camera(){}


glm::mat4 Camera::getProjectionMatrix() const {

    return this->m4ProjectionMatrix;

}

// PerspectiveCamera

PerspectiveCamera::PerspectiveCamera( float fov , float aspect , float near , float far )
    : fov( fov ) , aspect( aspect ) , near( near ) , far( far ) , Camera()
{
    this->updateProjectionMatrix();
    this->updateFrustum();
}

PerspectiveCamera::~PerspectiveCamera(){}

void PerspectiveCamera::updateFrustum(){
    
}
    
void PerspectiveCamera::updateProjectionMatrix(){
    float PI = M_PI;
    this->m4ProjectionMatrix = glm::perspective( fov * PI / 180.0f , aspect , near , far );
}

void PerspectiveCamera::init(){

}

void PerspectiveCamera::update( float deltaTime ){
    
}

// Orthographic Camera 

OrthogonalCamera::OrthogonalCamera( float left , float right , float top , float bottom , float near , float far )
    : left( left ) , right( right ) , top( top ) , bottom( bottom ) , near( near ) , far( far )
{
    this->updateProjectionMatrix();
    this->updateFrustum();
}

void OrthogonalCamera::updateFrustum(){

}

void OrthogonalCamera::updateProjectionMatrix(){

    this->m4ProjectionMatrix = glm::ortho( left , right , bottom , top , near , far );

}

void OrthogonalCamera::init(){}

void OrthogonalCamera::update( float deltaTime ) {

}


