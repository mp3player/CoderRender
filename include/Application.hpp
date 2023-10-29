#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_


#include <Window.hpp>
#include <system/System.hpp>
#include <system/CoordinateSystem.hpp>
#include <system/RenderSystem.hpp>
#include <system/TimeSystem.hpp>


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

        void addNode( ){ }

        void addMesh( std::string path ){

            Mesh * mesh = Mesh::ReadAttributeFromFile( path );
            Node * node = new Node();
            
            TransformComponent * transformComponent = new TransformComponent( );
            MeshComponent * meshComponent = new MeshComponent( mesh, "render" );

            node->addComponent( meshComponent );
            node->addComponent( transformComponent );

            this->scene->children.push_back( node );

        }


    private:
        static Application * application;
        

    public:
        static Application * getInstance();
        static void * release();


};



#endif 