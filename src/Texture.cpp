#include <scene/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.c"

#include <iostream>


#define R___ 0x2002
#define RG__ 0x8227
#define RGB_ 0x1907
#define RGBA 0x1908


Texture2D::Texture2D( std::string path )
    : path( path ) , width( 0 ) , height( 0 )
{
    this->loadImageData( path );
}

Texture2D::~Texture2D(){
    this->dispose();
}

int Texture2D::getWidth() const {
    return this->width;
}

int Texture2D::getHeight() const {
    return this->height;
}

int Texture2D::getChannel() const {
    return this->channel;
}

unsigned int Texture2D::getFormat() const {
    
    return this->format;

}

unsigned char * Texture2D::ptr() const {
    return this->data;
}

void Texture2D::loadImageData( std::string path ){
    
    if( this->data != nullptr ){
        this->dispose();
    }

    this->data = stbi_load( this->path.c_str() , &( this->width ) , &( this->height ) , &( this->channel ) , 0 );
    
    if( this->data == nullptr ){
        // error
        return ;
    }

    if( this->channel == 1 ){

        this->format = R___;

    }else if( this->channel == 2 ){

        this->format = RG__;

    }else if( this->channel == 3 ){

        this->format == RGB_;

    }else if( this->channel == 4 ){

        this->format == RGBA;

    }

}

void Texture2D::dispose(){

    if( this->data != nullptr ){
        stbi_image_free( this->data );
        this->data = nullptr;
    }

}

