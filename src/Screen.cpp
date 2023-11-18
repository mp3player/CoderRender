#include <scene/Screen.hpp>
#include <core/Buffer.hpp>


std::vector< float > vertex = { 1.0f , 1.0f , -1.0f , 1.0f , -1.0f , -1.0f , 1.0f , -1.0f };
std::vector< float > uv = { 1.0f , 1.0f , 0.0f , 1.0f , 0.0f , 0.0f , 1.0f , 0.0f };
std::vector< unsigned int > _index = { 0 , 1 , 2 , 0 , 2 , 3 };

Screen::Screen(){

    this->vao = new VertexArrayBuffer();
    this->vao->addAttribute( vertex , 2 );
    this->vao->addAttribute( uv , 2 );
    this->vao->setIndex( _index );

    this->vao->unBind();
    
}

Screen::~Screen(){
    delete this->vao;
}


void Screen::render(){

    this->vao->bind();

    glDrawElements( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

    this->vao->unBind();

}