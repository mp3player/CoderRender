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

LightType Light::lightType() const {
    return LIGHT;
}








AmbientLight::AmbientLight( glm::vec3 color , float intensity )
    : Light( color , intensity )
{}

LightType AmbientLight::lightType() const {
    return AMBIENT;
}












DirectionalLight::DirectionalLight( glm::vec3 color , float intensity )
    : Light( color , intensity )
{}

LightType DirectionalLight::lightType() const {
    return DIRECTIONAL;
}









SpotLight::SpotLight::SpotLight( glm::vec3 color , float intensity )
    : Light( color , intensity )
{}

LightType SpotLight::lightType() const {
    return SPOT;
}
