#ifndef _COMPONENT_TRANSFORM_HPP_
#define _COMPONENT_TRANSFORM_HPP_

#include <component/Component.hpp>
#include <glm/glm.hpp>


const glm::vec3 O = glm::vec3( 0.0f , 0.0f , 0.0f );
const glm::vec3 X = glm::vec3( 1.0f , 0.0f , 0.0f );
const glm::vec3 Y = glm::vec3( 0.0f , 1.0f , 0.0f );
const glm::vec3 Z = glm::vec3( 0.0f , 0.0f , 1.0f );
const glm::mat3 M3ID = glm::mat3( 1.0f );
const glm::mat4 M4ID = glm::mat4( 1.0f );


struct Transform : Component {

    public:
        
        glm::vec3 v3Translation = O;
        glm::vec3 v3Scale = glm::vec3( 1.0f , 1.0f , 1.0f );
        glm::vec3 v3Rotation = O;

    public:

        glm::vec3 v3LookAt = -Z;
        glm::vec3 v3Right = X;
        glm::vec3 v3Up = Y;


    public:
        
        glm::mat4 m4ModelMatrix = M4ID;
        glm::mat4 m4InverseModelMatrix = M4ID;
        glm::mat3 m3NormalMatrix = M3ID;

        glm::mat4 m4WorldMatrix = M4ID;
        glm::mat4 m4InverseWorldMatrix = M4ID;

        glm::mat4 m4ModelWorldMatrix = M4ID;
        glm::mat4 m4InverseModelWorldMatrix = M4ID;
        glm::mat3 m3NormalWorldMatrix = M3ID;

        glm::mat4 m4ViewMatrix = M4ID;
        glm::mat4 m4InverseViewMatrix = M4ID;


    public:

        Transform(  );

    public:

        void setTranslation( glm::vec3 ) ;
        void setRotation( glm::vec3 );
        void setScale( glm::vec3 );

        void translate( float x = 0.0f , float y = 0.0f , float z = 0.0f ); 
        void scale( float x = 1.0f , float y = 1.0f , float z = 1.0f );
        void rotate( float x = 0.0f , float y = 0.0f , float z = 0.0f );

    public:

        void setWorldTransform( glm::mat4 worldTransform , glm::mat4 inverseWorldTransform );
        void updateModelTransform();
        void updateViewTransform();
        void updateModelWorldTransform();

    public:
        void init() override;

        void update( float deltaTime ) override ;

};


#endif