#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_


#include <Window.hpp>
#include <system/System.hpp>
#include <system/CoordinateSystem.hpp>
#include <system/RenderSystem.hpp>
#include <system/TimeSystem.hpp>
#include <scene/Screen.hpp>


// single Instance Application
struct Application {

    public:
        Window * window;

        Scene * scene;

        RenderSystem * renderSystem;
        CoordinateSystem * coordinateSystem;
        TimeSystem * timeSystem;

        std::vector< System * > systems;

    private:
        Application() = default ;

    public:
        ~Application();

    public:

        void registSystem( System * system );

        void init();
        
        void run();

        void update( float deltaTime );

    public:

        Node * addNode( );

        Node * addNode( std::string path );

        Node * addCamera();

        Node * addAmbientLight();
        
        Node * addDirectionalLight();

        Node * addSpotLight();

        Node * addPointLight();


    private:
        static Application * application;
        

    public:
        static Application * getInstance();
        static void * release();


};



#endif 