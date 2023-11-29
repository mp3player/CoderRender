#ifndef _PASS_HPP_
#define _PASS_HPP_

#include <core/VertexBuffer.hpp>
#include <opengl/shader/OpenGLProgram.hpp>
#include <core/RenderBuffer.hpp>

struct Pass {

    public:
        int width ;
        int height;

    public:
        Pass( int width , int height );



};




struct FullScreenQuad {

    public:

        VertexArrayBuffer * vao;
        Program * program;

    public:

        FullScreenQuad();
        ~FullScreenQuad();

    public:

        void render( RenderTexture * texture );

};












#endif