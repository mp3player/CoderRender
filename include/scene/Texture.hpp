#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>



struct Texture {

    protected:
        unsigned char * data = nullptr ;
        int width;
        int height;

    public:
        GLenum wrapS;
        GLenum wrapT;
        GLenum magFilter;
        GLenum minFilter;

    public:
        Texture() = default;
        virtual ~Texture() ;

        int getWidth() const ;
        int getHeight() const ;

        void * ptr() const;
        
        virtual void dispose();
};

struct ImageTexture : Texture {
    
    private:
        int channel;

    public:
        ImageTexture( int width , int height , int channel );
        ImageTexture( std::string path );
        ~ImageTexture( );

    public:
        int getChannel() const ;

        bool setColor( int x , int y , glm::vec3 color );
        glm::vec3 getColor( int x , int y );

        void drawLine( int x0 , int y0 , int x1 , int y1 );
        void drawCircle( int x , int y , int r );
        void drawRect( int x0 , int y0 , int width , int height );

        // void drawPolygon();

};

// VideoTexture
// 

ImageTexture noise( int width , int height , int octave );

ImageTexture noise( int width , int height , std::vector< int > octave );




#endif