#include <Application.hpp>
#include <core/Buffer.hpp>
#include <opengl/shader/Program.hpp>

Program * p = Program::FromFile(
    "/home/coder/project/c++/engine/shader/basic/vertex.vert" , 
    "/home/coder/project/c++/engine/shader/basic/fragment.frag" 
    );

Application::~Application(){

    delete this->window;
    delete this->scene;
    delete this->renderSystem;
    delete this->coordinateSystem;
    delete this->timeSystem;

    delete p;

}

void Application::registSystem( System * system ){
    this->systems.push_back( system );
}

void Application::init(){

    this->window = new Window( 800 , 600 , "OpenGL" );
    this->scene = new Scene();
    
    this->renderSystem = new RenderSystem( this->scene );
    this->coordinateSystem = new CoordinateSystem( this->scene );
    this->timeSystem = new TimeSystem( this->scene );
    // this->addMesh( "/home/coder/project/c++/engine/monkey.obj" );

    p->compile();

}

void Application::run(){


    Mesh * mesh = Mesh::ReadAttributeFromFile( "/home/coder/project/c++/engine/monkey.obj" );

    AttributeFloat * position = mesh->getAttribute("position");
    VertexArrayBuffer vao;
    vao.init();
    vao.bind();
    vao.addAttribute( position );


    delete mesh;
    float time = 0.;
    while( !window->shouldClose() ){
        float deltaTime = this->timeSystem->getDeltaTime();

        // this->coordinateSystem->update( deltaTime );
        // this->renderSystem->update( deltaTime );

        this->update( deltaTime );
        
        p->bind();
        p->setUniformValue("time" , time);
        time += 0.1f;
        // glBindVertexArray( vao );
        vao.bind();
        glPointSize( 100.0f );
        glDrawArrays( GL_POINTS , 0 , 2 );
    }
}

void Application::update( float deltaTime ){
    this->window->pollEvent();
    this->window->swapBuffer();
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
    if( Application::application == nullptr ){
        delete Application::application;
        Application::application == nullptr ;
    }
}