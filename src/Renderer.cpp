#include <render/Renderer.hpp>




Renderer::~Renderer(){}

void Renderer::setColor( float r , float g , float b ){
    this->color = glm::vec3( r , g , b );
}

void Renderer::setColor( glm::vec3 color ){
    this->setColor( color.r , color.g , color.b );
}

void Renderer::setAlpha( float alpha ){
    this->alpha = alpha;
}



