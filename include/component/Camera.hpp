#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <iostream>
#include <component/Component.hpp>

std::ostream & operator << ( std::ostream & cout , glm::mat4 vec );
std::ostream & operator << ( std::ostream & cout , glm::vec3 vec );

struct Camera : Component {

    protected:
        glm::mat4 m4ProjectionMatrix = glm::mat4( 1.0f );
        glm::mat4 m4InverseProjectionMatrix = glm::mat4( 1.0f );

        glm::mat4 m4ViewMatrix = glm::mat4( 1.0f );
        glm::mat4 m4InverseViewMatrix = glm::mat4( 1.0f );

        glm::mat4 m4ViewProjectionMatrix = glm::mat4( 1.0f );
        glm::mat4 m4InverseViewProjectionMatrix = glm::mat4( 1.0f );

    protected :
        glm::vec3 v3Position = glm::vec3( 0.0f );
        glm::vec3 v3LookAt = glm::vec3( 0.0f , 0.0f , 0.0f );
        glm::vec3 v3Up = glm::vec3( 0.0f , 1.0f , 0.0f );

    public:
        Camera() = default;
        virtual ~Camera();

        virtual void updateFrustum() = 0;
        virtual void updateProjectionMatrix() = 0;
        virtual void updateViewMatrix();
        virtual void updateViewProjectionMatrix();

        virtual glm::mat4 getProjectionMatrix();
        virtual glm::mat4 getViewMatrix();
        virtual glm::mat4 getViewProjectionMatrix();

        void setPosition( glm::vec3 );
        void setLookAt( glm::vec3 );
        void setUp( glm::vec3 );

    // public: 
    //     void init() override;
    //     void update( float deltaTime ) override;


};

struct PerspectiveCamera : public Camera {

    private:
        float fov;
        float aspect ;
        float near ;
        float far ;

    public:

        explicit PerspectiveCamera( float fov , float aspect , float near , float far );
        ~PerspectiveCamera();

        void updateFrustum() override;
        void updateProjectionMatrix() override ;

    public :
        void init() override;
        void update( float deltaTime ) override;

};

struct OrthogonalCamera : public Camera {

    private :
        float left ;
        float right;
        float top;
        float bottom;
        float near ; 
        float far;

    public:
        explicit OrthogonalCamera( float left , float right , float top , float bottom , float near , float far );
        
        void updateFrustum() override;
        void updateProjectionMatrix() override ;

    public:
        void init() override;
        void update( float deltaTime ) override;

};

#endif 