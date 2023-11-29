#include <core/TextureBuffer.hpp>



float defaultColor[ ] = { 1.0f , 1.0f , 1.0f };



void TextureBuffer::init() {
    this->init( GL_TEXTURE_2D );
}

void TextureBuffer::bind() {
    glBindTexture( this->target , this->id );
}

void TextureBuffer::unBind() {
    glBindTexture( this->target , 0 );
}

void TextureBuffer::dispose() {
    if( glIsTexture( this->id ) )
        glDeleteTextures( 1 , &(this->id) );
}

void TextureBuffer::init( GLenum target ){
    this->target = target;
    glCreateTextures( this->target , 1 , &( this->id ) );
}





template<>
void TextureBuffer::bufferData( Texture * img ){

    TextureImage * texture = ( TextureImage *)img;

    GLenum format = formats.at( texture->getChannel() );

    glTexParameteri( this->target , GL_TEXTURE_MIN_FILTER , texture->minFilter );
    glTexParameteri( this->target , GL_TEXTURE_MAG_FILTER , texture->magFilter );
    glTexParameteri( this->target , GL_TEXTURE_WRAP_S , texture->wrapS );
    glTexParameteri( this->target , GL_TEXTURE_WRAP_T , texture->wrapT );

    glTexImage2D( this->target , 0 , format , texture->getWidth() , texture->getHeight() , 0 , format , GL_UNSIGNED_BYTE , (void*)( texture->ptr() ) );

}