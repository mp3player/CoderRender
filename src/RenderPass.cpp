#include <render/RenderPass.hpp>
#include <component/Camera.hpp>

// OpenGLRenderTarget( Frame Buffer );
RenderPass::RenderPass( int width , int height )
    :width( width ) , height( height )
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

    // bind Buffer
    this->frameBuffer->bind();

    // depth buffer 
    this->depthBuffer->allocate( GL_DEPTH_COMPONENT );

    glFramebufferRenderbuffer( GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER , this->depthBuffer->ID() );

    // render to texture => not need color render buffer
    this->renderTexture->bind();

    glFramebufferTexture( GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , this->renderTexture->ID() , 0 );

    // TODO : may need stencil buffer & multi-sample buffer

    this->depthBuffer->unBind();
    this->renderTexture->unBind();
    this->frameBuffer->unBind();

}

void RenderPass::dispose(){
    
    delete this->frameBuffer;
    delete this->depthBuffer;
    delete this->renderTexture;

}

