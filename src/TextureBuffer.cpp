#include <core/TextureBuffer.hpp>


void TextureBuffer::init() {
    glGenTextures( 1 , &( this->id ) );
}

void TextureBuffer::bind( GLenum target ) {
    glBindTexture( target , this->id );
}

void TextureBuffer::unBind() {
    glBindTexture( this->target , 0 );
}

void TextureBuffer::dispose() {
    if( glIsTexture( this->id ) )
        glDeleteTextures( 1 , &(this->id) );
}


void TextureBuffer::bind(){
    this->bind( GL_TEXTURE );
}