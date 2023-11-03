#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <string>
#include <scene/Texture.hpp>

struct Material {

    public:
        bool castShadow = false;
        bool receiveShadow = false;

        glm::vec3 v3Color;

        Texture * map = nullptr ;
        Texture * diffuseMap = nullptr ;
        Texture * specularMap = nullptr ;
        Texture * normalMap = nullptr ;

    public:

        Material() = default;
        ~Material() = default;

};



#endif