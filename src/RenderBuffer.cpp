#include <core/RenderBuffer.hpp>

// Render Buffer 
RenderBuffer::RenderBuffer( int width , int height )
    : width( width ) , height( height )
{}

void RenderBuffer::init(){
    glGenRenderbuffers( 1 , &( this->id ) );
}

void RenderBuffer::bind( GLenum target ){
    glBindRenderbuffer( GL_RENDERBUFFER , this->id );
}

void RenderBuffer::unBind(){
    glBindRenderbuffer( GL_RENDERBUFFER , 0 );
}

void RenderBuffer::dispose(){
    if( glIsRenderbuffer( this->id ) ){
        glDeleteRenderbuffers( 1 , &( this->id ) );
    }
}

void RenderBuffer::bind(){
    this->bind( GL_RENDERBUFFER );
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
    glGenTextures( 1 , &( this->id ) );
}

void RenderTexture::bind( GLenum target ){
    glBindTexture( target , this->id );
}

void RenderTexture::unBind(){
    glBindTexture( target , 0 );
}

void RenderTexture::dispose(){
    if( glIsTexture( this->id ) ){
        glDeleteTextures( 1 , &( this->id ) );
    }
}

void RenderTexture::bind(){
    this->bind( GL_TEXTURE_2D );
}



// FrameBuffer 

FrameBuffer::FrameBuffer( int width , int height )
    : width( width ) , height( height )
{}

void FrameBuffer::init() {
    glGenFramebuffers( 1 , &( this->id ) );

}

void FrameBuffer::bind( GLenum target ){
    this->target = target;
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

void FrameBuffer::bind(){
    this->bind( GL_FRAMEBUFFER );
}


