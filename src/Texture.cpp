#include <scene/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.c"
#include <iostream>

// TODO : texture data should be stored in Resource Manager to prevent the destructor calling automaticly in local variables;

Texture::~Texture(){
    
}

int Texture::getWidth() const {
    return this->width;
}

int Texture::getHeight() const {
    return this->height;
}

void * Texture::ptr() const {
    return this->data;
}

void Texture::dispose(){
    if( this->data != nullptr ) delete data;
}


// Texture2D


// ImageTexture 

ImageTexture::ImageTexture( int width , int height , int channel )
    : channel( channel )
{
    this->width = width;
    this->height = height;

    srand( time( NULL ) );
    // allocate memory to store the data of the picture
    this->data = new unsigned char[ this->width * this->height * this->channel ];
    for( int i = 0 ; i < this->width ; ++i ){
        for( int j = 0 ; j < this->height ; ++ j ){

            float c = 0.0f;
            setColor( i , j , glm::vec3( c ) );

        }
    }
}

ImageTexture::ImageTexture( std::string path ){
    this->data = stbi_load(path.c_str() , &(this->width) , &(this->height) , &(this->channel) , 0);
}

ImageTexture::~ImageTexture(){

}


int ImageTexture::getChannel() const {

    return this->channel;

}

bool ImageTexture::setColor( int x , int y , glm::vec3 color ){
    if( x < 0 || y < 0 || x >= this->width || y >= this->height ) return false;

    int index = y * this->width + x;
    this->data[ index * 3 + 0 ] = (unsigned char) ( color.r * 255 );
    this->data[ index * 3 + 1 ] = (unsigned char) ( color.g * 255 );
    this->data[ index * 3 + 2 ] = (unsigned char) ( color.b * 255 );

    return true;
}

glm::vec3 ImageTexture::getColor( int x , int y ){
    if( x < 0 || y < 0 || x >= this->width || y >= this->height ) return glm::vec3( 0.0f );
    int index = y * this->width + x;
    unsigned char r = this->data[ index * 3 + 0 ];
    unsigned char g = this->data[ index * 3 + 1 ];
    unsigned char b = this->data[ index * 3 + 2 ];

    return glm::vec3( r / 255.0f , g / 255.0f , b / 255.0f );
}

void ImageTexture::drawLine( int x0 , int y0 , int x1 , int y1 ){
    // calculate the equation of the line
    float slope = float( y1 - y0 ) / float( x1 - x0 );
    float bias = float( y1 ) - slope * float( x1 );
    int step = ( x1 - x0 ) / std::abs( x1 - x0 );


    for( int i = 0 ; i < std::abs( x1 - x0 ) ; ++ i ){
        int x = x0 + i * step ;
        int y = slope * x + bias;
        float c = ( rand() % 1000 ) / 1000.0f ;
        setColor( x , y , glm::vec3( c ) );
    }
}


