#include <core/RenderBuffer.hpp>
#include <cassert>

// Render Buffer 
RenderBuffer::RenderBuffer( int width , int height )
    : width( width ) , height( height )
{}

void RenderBuffer::init(){
    glCreateRenderbuffers( 1 , &( this->id ) );
}

void RenderBuffer::bind(){
    glBindRenderbuffer( this->target , this->id );
}

void RenderBuffer::unBind(){
    glBindRenderbuffer( GL_RENDERBUFFER , 0 );
}

void RenderBuffer::dispose(){
    if( glIsRenderbuffer( this->id ) ){
        glDeleteRenderbuffers( 1 , &( this->id ) );
    }
}

void RenderBuffer::allocate( GLenum component ){

    this->component = component;
    // stablish data storage, format and dimensions of a renderbuffer object's image
    glRenderbufferStorage( this->target , component ,this->width , this->height );

}




// Render Texture 
RenderTexture::RenderTexture( int width , int height )
    : width( width ) , height( height )
{}

void RenderTexture::init(){
    glCreateTextures( GL_TEXTURE_2D , 1 , &( this->id ) );
}

void RenderTexture::bind(){
    glBindTexture( this->target , this->id );
}

void RenderTexture::unBind(){
    glBindTexture( target , 0 );
}

void RenderTexture::dispose(){
    if( glIsTexture( this->id ) ){
        glDeleteTextures( 1 , &( this->id ) );
    }
}




// FrameBuffer 

FrameBuffer::FrameBuffer( int width , int height )
    : width( width ) , height( height )
{}

void FrameBuffer::init() {
    glCreateFramebuffers( 1 , &( this->id ) );
}

void FrameBuffer::bind(){
    glBindFramebuffer( target , this->id );
}

void FrameBuffer::unBind(){
    glBindFramebuffer( this->target , 0 );
}

void FrameBuffer::dispose(){
    if( glIsFramebuffer( this->id ) ) {
        glDeleteFramebuffers( 1 , &( this->id ) );
    }
}

void FrameBuffer::bindRenderBuffer( RenderBuffer * renderbuffer , GLenum format , GLenum attachment ){
    
    this->bind();
    renderbuffer->bind();
    glRenderbufferStorage( this->target , format , this->width , this->height );
    glFramebufferRenderbuffer( this->target , attachment , renderbuffer->getTarget() , renderbuffer->ID() );

}

void FrameBuffer::bindRenderTexture( RenderTexture * texture , GLenum attachment , int level ){

    texture->bind();
    glNamedFramebufferTexture( this->id , attachment , texture->ID() , 0 );

}

void FrameBuffer::drawBuffer(  std::vector< GLenum > attachments  ){

    glDrawBuffers( attachments.size() , attachments.data() );

}

void FrameBuffer::copy( FrameBuffer * destination , int sx , int sy , int sw , int sh , int dx , int dy , int dw , int dh , unsigned char mask , unsigned int filter ){
    
    assert( destination != nullptr );

    unsigned int sTarget = this->target;
    unsigned int dTarget = destination->getTarget();

    this->setTarget( GL_READ_FRAMEBUFFER );
    destination->setTarget( GL_DRAW_FRAMEBUFFER );

    this->bind();
    destination->bind();

    glBlitFramebuffer( sx , sy , sw , sh , dx , dy , dw , dh , mask , filter );

    destination->unBind();
    this->unBind(); 

    this->setTarget( sTarget );
    destination->setTarget( dTarget );

}

