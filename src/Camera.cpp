#include <component/Camera.hpp>
#include <glm/ext.hpp>



std::ostream & operator << ( std::ostream & cout , glm::mat4 mat ){
    for( int i = 0 ; i < 4 ; ++ i ){
        for( int j = 0 ; j < 4 ; ++ j ){
            std::cout << mat[ i ][ j ] << "\t";
        }
        std::cout << std::endl;
    }
    return cout;
}


std::ostream & operator << ( std::ostream & cout , glm::vec3 vec ){

    std::cout << vec.x << " " << vec.y << " " << vec.z ;
    return cout;

}

// Camera
Camera::~Camera(){}

void Camera::updateViewMatrix(){

    this->m4ViewMatrix = glm::lookAt( this->v3Position , this->v3LookAt , this->v3Up );
    
}

void Camera::updateViewProjectionMatrix(){
    this->m4ViewProjectionMatrix = this->m4ProjectionMatrix * this->m4ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(){
    return this->m4ProjectionMatrix;
}

glm::mat4 Camera::getViewMatrix(){
    return this->m4ViewMatrix;
}

glm::mat4 Camera::getViewProjectionMatrix(){
    return this->m4ViewProjectionMatrix;
}

void Camera::setPosition( glm::vec3 position ){
    this->v3Position = position;
    this->needUpdate = true;
}

void Camera::setLookAt( glm::vec3 lookAt ){
    this->v3LookAt = lookAt;
    this->needUpdate = true;
}

void Camera::setUp( glm::vec3 up ){
    this->v3Up = up;
    this->needUpdate = true;
}

// PerspectiveCamera

PerspectiveCamera::PerspectiveCamera( float fov , float aspect , float near , float far )
    : fov( fov ) , aspect( aspect ) , near( near ) , far( far ) 
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

void OrthogonalCamera::update( float deltaTime ) {}


