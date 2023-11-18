#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>



struct Texture {

    public:

        glm::vec2 v2Offset;
        glm::vec2 v2Scale;
        float v1Rotation;

    public:

        GLenum wrapS;
        GLenum wrapT;
        GLenum magFilter;
        GLenum minFilter;

};


struct Texture2D : Texture {

    private:

        std::string path;    
        int width;
        int height;
        int channel;
        unsigned int format;
        unsigned char * data = nullptr;

    public:

        Texture2D() = default;
        Texture2D( std::string path );
        ~Texture2D();

    public:

        int getWidth() const ;
        int getHeight() const ;
        int getChannel( ) const ;
        unsigned int getFormat() const ;

        unsigned char * ptr() const;


    public:

        void loadImageData( std::string path );
        void dispose();

};


struct Texture3D : Texture {

};

struct Texture2DArray : Texture {

};


#endif