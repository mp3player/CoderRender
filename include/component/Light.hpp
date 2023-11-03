#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include <glm/glm.hpp>
#include <component/Camera.hpp>
#include <component/Component.hpp>

enum LightType {
    LIGHT , AMBIENT , DIRECTIONAL , SPOT
};

struct Light : Component {
    
    float intensity;
    glm::vec3 color;

    explicit Light( glm::vec3 color = glm::vec3( 1.0f ) , float intensity = 1.0f );

    public:

        void init() override;
    
        void update( float deltaTime ) override;

    public:

        virtual LightType lightType() const ;

};

struct AmbientLight : Light {
    
    public:
        
        explicit AmbientLight( glm::vec3 color , float intensity );

    public:

        LightType lightType() const override ;

};

struct DirectionalLight : Light {

    explicit DirectionalLight( glm::vec3 color , float intensity );

    public:

        LightType lightType() const override ;

};

struct SpotLight : Light {

    explicit SpotLight( glm::vec3 color , float intensity );

    public:

        LightType lightType() const override ;

};




#endif 