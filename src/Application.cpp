#include <Application.hpp>
#include <core/Buffer.hpp>
#include <opengl/shader/Program.hpp>
#include <component/Camera.hpp>
#include <component/Light.hpp>

#define WIDTH 800
#define HEIGHT 800

Node * node = nullptr ;

Application::~Application(){

    delete this->scene;
    delete this->renderSystem;
    delete this->coordinateSystem;
    delete this->timeSystem;
    delete this->screen;
    delete this->pass;
    delete this->window;

}

void Application::registSystem( System * system ){

    this->systems.push_back( system );

}

void Application::init(){

    this->window = new Window( WIDTH , HEIGHT , "OpenGL" );


    this->scene = new Scene();
    
    this->renderSystem = new RenderSystem( this->scene );
    this->coordinateSystem = new CoordinateSystem( this->scene );
    this->timeSystem = new TimeSystem( this->scene );
    Node * monkey = this->addNode( "/home/coder/project/c++/engine/monkey.obj" );
    Node * cube = this->addNode( "/home/coder/project/c++/engine/cube.obj" );

    cube->getComponent<Transform>()->translate( 2 , 0, 0 );

    Node * camera = this->addCamera();

    Node * light = this->addLight();

    node = cube;


    // render pass
    // this->screen = new Screen();
    // this->pass = new RenderPass( WIDTH , HEIGHT );


}

void Application::run(){

    while( !window->shouldClose() ){


        float deltaTime = this->timeSystem->getDeltaTime();

        // this->pass->render( this->scene );

        // this->screen->render();

        this->coordinateSystem->update( deltaTime );
        this->renderSystem->update( deltaTime );



        if( node == nullptr ) continue;
        node->getComponent<Transform>()->rotate( .01f , .01f  );



        this->update( deltaTime );

    }
}

void Application::update( float deltaTime ){



    this->window->pollEvent();
    this->window->swapBuffer();

}

Node * Application::addNode( std::string path ){

    Mesh * mesh = Mesh::ReadAttributeFromFile( path );
    Node * node = new Node();

    MeshComponent * meshComponent = new MeshComponent( mesh );
    RenderComponent * renderComponent = new RenderComponent( );

    node->addComponent( meshComponent );
    node->addComponent( renderComponent );

    this->scene->addChild( node );

    return node;

}

Node * Application::addCamera(){

    Node * node = new Node();
    Camera * camera = new PerspectiveCamera(45 , 1.0f , .1f , 1000.0f );
    node->addComponent( camera );
    node->setName( "mainCamera" );

    Transform * transform = node->getComponent< Transform >();

    transform->setTranslation( glm::vec3( 0 , 5 , 5 ) );
    transform->rotate( -45 * M_PI / 180.0f , 0 , 0 );
    // transform->scale( .1f , .1f , .1f );

    this->scene->addChild( node );

    return node;
    
}

Node * Application::addLight(){

    Node * node = new Node();
    Light * light = new AmbientLight( glm::vec3( 1.0f , 1.0f , 0.0f ) , 1.0f );

    node->addComponent( light );

    this->scene->addChild( node );

    return node;

}

// ------------------------------------------------------------------------

Application * Application::application = nullptr;

Application * Application::getInstance(){

    if( Application::application == nullptr ){
        Application::application = new Application();
        Application::application->init();
    }

    return Application::application;

}


void * Application::release(){

    delete Application::application;
    Application::application == nullptr ;

}