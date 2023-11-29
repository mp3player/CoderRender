#include <Application.hpp>
#include <core/Buffer.hpp>
#include <opengl/shader/OpenGLProgram.hpp>
#include <component/Camera.hpp>
#include <component/Light.hpp>
#include <component/Transform.hpp>
#include <cmath>

#define MOUSEDOWN 1
#define MOUSEUP 0

#define BUTTONLEFT 0
#define BUTTONRIGHT 1 
#define BUTTONMIDDLE 2

#define UP 87
#define DOWN 83
#define LEFT 65
#define RIGHT 68
#define SPACE 32



#define WIDTH 800
#define HEIGHT 800

Node * mainCamera = nullptr ;

Node * node = nullptr ;

Node * lightNode = nullptr ;

bool mouseDown = false;
int btn = -1;
glm::vec2 position;

void MouseEventHandler(GLFWwindow* window, int button, int action, int mods){

    if( action == MOUSEDOWN ) {
        btn = button;
        mouseDown = true;
        double x , y ;
        glfwGetCursorPos( window , &x , &y );
        position = glm::vec2( x , y );
    }else {
        mouseDown = false;
        btn = -1;
    }
    // action => 1 down , 0 up
    // button => 0 left , 1 right , 2 middle

};

void KeyEventHandler( GLFWwindow* window, int key, int scancode, int action, int mods ){

    // action => 1 down , 0 up
    // key => keyCode
    // w : 87 , s : 83 , a : 65 , d : 68



    if( mainCamera == nullptr ) return ;

    Transform * t = mainCamera->getComponent< Transform >();

    if( t == nullptr ) return ;

    if( action == 1 ){
        switch( key ){
            case UP : { t->translate( 0 , 1 , 0 ); }break;
            case DOWN : { t->translate( 0 , -1 , 0 ); }break;
            case LEFT : { t->translate( -1 , 0 , 0 ); }break;
            case RIGHT : { t->translate( 1 , 0 , 0 ); }break;
            case SPACE : { 
                t->setTranslation( glm::vec3( 0 , 0 , 4 ) );
                t->setRotation( glm::vec3( 0 , 0 ,0 ) ) ;
            }break;
            default : {}break;
        }
    }

}

void ScrollEventHandler( GLFWwindow* window, double xoffset, double yoffset ){
    
    if( mainCamera == nullptr ) return ;

    Transform * transform = mainCamera->getComponent< Transform >();

    glm::vec3 lookAt = transform->v3LookAt;

    glm::vec3 direction = glm::normalize( transform->v3LookAt - transform->v3Translation );

    direction.x *= yoffset;
    direction.y *= yoffset;
    direction.z *= yoffset;

    glm::vec3 position = glm::normalize( direction ) + transform->v3Translation;

    transform->setTranslation( position );

}

void MouseMoveHandler(GLFWwindow* window, double xpos, double ypos){

    if( mouseDown && mainCamera != nullptr ){

        glm::vec2 offset = -( glm::vec2( xpos , ypos ) - position ) * .005f;

        if( btn == BUTTONLEFT ){
            mainCamera->getComponent< Transform >()->rotate( offset.y , offset.x );
        }else if( btn == BUTTONMIDDLE ){
            mainCamera->getComponent< Transform >()->translate( -offset.x , offset.y , 0.0f );
        }



        position = glm::vec2( xpos , ypos );

        
    }
    
}

Application::Application( int width , int height , std::string title ){

    this->window = new Window( width , height , title );
    this->scene = new Scene();

    this->renderSystem = new RenderSystem( this->scene );
    this->coordinateSystem = new CoordinateSystem( this->scene );
    this->timeSystem = new TimeSystem( this->scene );

}

Application::~Application(){

    delete this->scene;
    delete this->renderSystem;
    delete this->coordinateSystem;
    delete this->timeSystem;


    delete this->window;

}




void Application::registSystem( System * system ){

    this->systems.push_back( system );

}

void Application::init(){

    // Node * plane = this->addNode( "/home/coder/project/c++/engine/assets/models/plane.obj" );
    // this->scene->addChild( plane );
    // plane->getComponent< Transform >()->rotate( glm::radians( -10.0f ) , 0 , 0 );

    Node * monkey = this->addNode( "/home/coder/project/c++/engine/assets/models/toru.obj" );
    monkey->getComponent< Transform >()->translate( -0.5 , 0 , 0 ); 
    

    Node * cube = this->addNode( "/home/coder/project/c++/engine/assets/models/cube.obj" );
    cube->getComponent<Transform>()->translate( .5 , 0, 0 );

    cube->addChild( monkey );
    this->scene->addChild( cube );

    mainCamera = this->addCamera();

    Node * alight = this->addAmbientLight();
    Node * dlight = this->addDirectionalLight();
    // Node * sLight = this->addSpotLight();
    Node * pLight = this->addPointLight();
    pLight->getComponent< Transform >()->setTranslation( glm::vec3( 1.0f ) );

    node = cube;

    RenderComponent * render = node->getComponent<RenderComponent>();

    Material * mat = render->material;

    TextureImage * img = new TextureImage("/home/coder/project/c++/engine/assets/pictures/fire_shader_8.png");

    mat->addUniformValue< Texture* >( "map" , img );

    glfwSetMouseButtonCallback(this->window->window , MouseEventHandler );
    glfwSetKeyCallback( this->window->window , KeyEventHandler );
    glfwSetScrollCallback( this->window->window , ScrollEventHandler );
    glfwSetCursorPosCallback( this->window->window , MouseMoveHandler );

}

// TODO : create a thread to call init function 

void Application::run(){

    while( !window->shouldClose() ){

        float deltaTime = this->timeSystem->getDeltaTime();
        
        this->coordinateSystem->update( deltaTime );
        this->renderSystem->update( deltaTime );


        if( node != nullptr ){
            node->getComponent<Transform>()->rotate( .009f  );
        }

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

    return node;

}

Node * Application::addCamera(){

    Node * node = new Node();
    Camera * camera = new PerspectiveCamera(45 , 1.0f , .1f , 1000.0f );
    // Camera * camera = new OrthogonalCamera(-5 , 5 , 5 , -5 , .1 , 10 );
    node->addComponent( camera );
    node->setName( "mainCamera" );

    Transform * transform = node->getComponent< Transform >();

    transform->setTranslation( glm::vec3( 0 , 8 , 8 ) );
    transform->rotate( -45 * M_PI / 180.0f );

    this->scene->addChild( node );

    return node;
    
}

Node * Application::addAmbientLight(){

    Node * node = new Node();
    Light * light = new AmbientLight( glm::vec3( 1.0f , 1.0f , 1.0f ) , .2f );

    node->addComponent( light );

    this->scene->addChild( node );

    return node;

}

Node * Application::addDirectionalLight(){

    Node * node = new Node();
    
    Light * light = new DirectionalLight( glm::vec3( 1.0f , 1.0f , 1.0f ) , .4f );

    node->addComponent( light );

    node->getComponent< Transform >()->translate( 0 , 10 , 10 );
    node->getComponent< Transform >()->rotate( -45 * M_PI / 180.0f , 0 ,0 );

    lightNode = node;

    this->scene->addChild( node );

    return node;

}

Node * Application::addSpotLight(){

    Node * node = new Node();
    
    Light * light = new SpotLight( glm::vec3( 1.0f , 1.0f , 1.0f ) , 1.0f );

    node->addComponent( light );
    node->getComponent< Transform >()->translate( 0 , 0 , 2 );

    lightNode = node;
    this->scene->addChild( node );

    return node;

}

Node * Application::addPointLight(){

    Node * node = new Node();
    
    Light * light = new PointLight( glm::vec3( 1.0f , 0.0f , 0.0f ) , 2.0f );

    node->addComponent( light );
    node->getComponent< Transform >()->setTranslation( glm::vec3( 0 , 9, 9 ) );

    lightNode = node;
    this->scene->addChild( node );

    return node;

}


// ------------------------------------------------------------------------

Application * Application::application = nullptr;

Application * Application::getInstance(){

    if( Application::application == nullptr ){
        Application::application = new Application( WIDTH , HEIGHT , "OpenGL" );
    }

    return Application::application;

}




void * Application::release(){

    delete Application::application;
    Application::application == nullptr ;

}