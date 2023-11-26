#include <component/Light.hpp>

Light::Light(  glm::vec3 color , float intensity )
    : intensity( intensity ) , color( color ) 
{
    this->name = "light";
}

void Light::init(){

}

void Light::update( float deltaTime ){

}







AmbientLight::AmbientLight( glm::vec3 color , float intensity )
    : Light( color , intensity )
{}












DirectionalLight::DirectionalLight( glm::vec3 color , float intensity )
    : Light( color , intensity )
{}






PointLight::PointLight( glm::vec3 color , float intensity )
    :Light( color , intensity )
{}




SpotLight::SpotLight::SpotLight( glm::vec3 color , float intensity )
    : Light( color , intensity )
{}
