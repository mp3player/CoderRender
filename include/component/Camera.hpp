#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <iostream>
#include <component/Component.hpp>


struct Camera : Component {

    protected:

        glm::mat4 m4ProjectionMatrix = glm::mat4( 1.0f );
        glm::mat4 m4InverseProjectionMatrix = glm::mat4( 1.0f );

    public:

        Camera( );
        virtual ~Camera();

    public:

        virtual void updateFrustum() = 0;
        virtual void updateProjectionMatrix() = 0;

        virtual glm::mat4 getProjectionMatrix();
    
    public:

        void updateViewMatrix();
        void updateViewProjectionMatrix();

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