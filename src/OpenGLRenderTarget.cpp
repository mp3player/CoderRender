#include <render/OpenGLRenderTarget.hpp>

OpenGLRenderTarget::OpenGLRenderTarget( int width , int height )
    :width( width ) , height( height )
{

    this->target = new RenderTexture( width , height );

}

OpenGLRenderTarget::~OpenGLRenderTarget(){
    
    this->dispose();

}

void OpenGLRenderTarget::init(){

    RenderTexture * texture = new RenderTexture( this->width , this->height );

}

void OpenGLRenderTarget::bind( ){

    

}

void OpenGLRenderTarget::unBind(){

}


void OpenGLRenderTarget::dispose(){

        delete this->target;

}