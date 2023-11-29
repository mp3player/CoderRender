#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_


#include <thread>
#include <Window.hpp>
#include <system/System.hpp>
#include <system/CoordinateSystem.hpp>
#include <system/RenderSystem.hpp>
#include <system/TimeSystem.hpp>
#include <render/RenderPass.hpp>

// thread
// single Instance Application
struct Application {

    public:
        Window * window = nullptr ;

        Scene * scene = nullptr ;

        RenderSystem * renderSystem = nullptr ;
        CoordinateSystem * coordinateSystem = nullptr ;
        TimeSystem * timeSystem = nullptr ;

        std::vector< System * > systems;



    private:
        Application( int width , int height , std::string title );

    public:
        ~Application();

    public:

        void registSystem( System * system );

        void init();

        void asynInit();
        
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