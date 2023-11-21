#include <scene/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.c"

#include <iostream>
#include <core/Log.hpp>


#define R___ 0x2002
#define RG__ 0x8227
#define RGB_ 0x1907
#define RGBA 0x1908


Texture::~Texture(){}

TextureImage::TextureImage( std::string path )
    : path( path ) , width( 0 ) , height( 0 )
{
    this->loadImageData( path );
}

TextureImage::~TextureImage(){
    this->dispose();
}

int TextureImage::getWidth() const {
    return this->width;
}

int TextureImage::getHeight() const {
    return this->height;
}

int TextureImage::getChannel() const {
    return this->channel;
}

void * TextureImage::ptr() const {
    return (void *)this->data;
}

void TextureImage::loadImageData( std::string path ){
    
    if( this->data != nullptr ){
        this->dispose();
    }

    this->data = stbi_load( this->path.c_str() , &( this->width ) , &( this->height ) , &( this->channel ) , 0 );
    
    if( this->data == nullptr ){
        // error
        Log::cout( __FILE__ , "failed to load image " , path );
        return ;
    }


}

void TextureImage::dispose(){

    if( this->data != nullptr ){
        stbi_image_free( this->data );
        this->data = nullptr;
    }

}

