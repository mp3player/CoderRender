#ifndef _COMPONENT_TRANSFORM_HPP_
#define _COMPONENT_TRANSFORM_HPP_

#include <component/Component.hpp>
#include <glm/glm.hpp>

struct Light : Component {

    float intensity;
    glm::vec3 color;

};


#endif