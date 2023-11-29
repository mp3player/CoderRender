#include <render/RenderPass.hpp>
#include <component/Camera.hpp>

// OpenGLRenderTarget( Frame Buffer );
RenderPass::RenderPass( int width , int height )
    :Pass( width , height )
{}

RenderPass::~RenderPass(){
    this->dispose();
}

void RenderPass::init(){

    this->frameBuffer = new FrameBuffer( width , height );
    this->depthBuffer = new RenderBuffer( width , height );
    this->renderTexture = new RenderTexture( width , height );

    // create Buffer
    this->frameBuffer->init();
    this->depthBuffer->init();
    this->renderTexture->init();
    
    // target
    this->frameBuffer->setTarget( GL_FRAMEBUFFER );
    this->depthBuffer->setTarget( GL_RENDERBUFFER );
    this->renderTexture->setTarget( GL_TEXTURE_2D );


    // TODO : 
}

void RenderPass::dispose(){
    
    delete this->frameBuffer;
    delete this->depthBuffer;
    delete this->renderTexture;

}

void RenderPass::render(){

}


