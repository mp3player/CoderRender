#ifndef _TEXTURE_BUFFER_HPP_
#define _TEXTURE_BUFFER_HPP_

#include <core/Buffer.hpp>
#include <scene/Texture.hpp>

#include <unordered_map>


static std::unordered_map< int , GLenum > formats = {
    { 1 , GL_R},
    { 2 , GL_RG},
    { 3 , GL_RGB},
    { 4 , GL_RGBA }
};



struct TextureBuffer : Buffer {
    

    public:
        void init() override ;
        void bind( GLenum target ) override ;
        void unBind() override ;

        void dispose() override ;

    public:

        template< typename T >
        void bufferData( T * texture );

    public: 
        void init( GLenum type );
        void bind();


};

template< typename T >
void TextureBuffer::bufferData( T * t ){
    
    Texture * texture = dynamic_cast< Texture * >( t );
    
    if( !texture ) return ;

    TextureImage * image = dynamic_cast< TextureImage * >( t );

    if( image ){
        TextureBuffer::bufferData< TextureImage >( image );
    }

}



#endif