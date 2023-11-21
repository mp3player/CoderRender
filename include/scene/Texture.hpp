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

        GLenum wrapS = GL_NEAREST;
        GLenum wrapT = GL_NEAREST;
        GLenum wrapR = GL_NEAREST;
        GLenum magFilter = GL_NEAREST;
        GLenum minFilter = GL_NEAREST;

    public:
        virtual void * ptr() const = 0;
        virtual ~Texture();

};


struct TextureImage : Texture {

    private:

        std::string path;
        int width;
        int height;
        int channel;
        unsigned char * data = nullptr;

    public:

        TextureImage() = default;
        TextureImage( std::string path );
        ~TextureImage() override;

    public:

        int getWidth() const ;
        int getHeight() const ;
        int getChannel( ) const ;

        void * ptr() const override;


    public:

        void loadImageData( std::string path );
        void dispose();

};

struct TextureCube : Texture {

    public:

        Texture * nx = nullptr ;
        Texture * px = nullptr ;

        Texture * ny = nullptr ;
        Texture * py = nullptr ;

        Texture * nz = nullptr ;
        Texture * pz = nullptr ;

    public:

        TextureCube();
        ~TextureCube();

    



};




#endif