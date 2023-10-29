#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include <glm/glm.hpp>
#include <component/Camera.hpp>
#include <component/Component.hpp>

struct Light : Component {
    
    float intensity;
    glm::vec3 color;

};

struct AmbientLight : Light {
    
};

struct DirectionalLight : Light {

    glm::vec3 center;
    glm::vec3 lookAt;

};


#endif 