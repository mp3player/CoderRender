#ifndef _OPENGL_RENDER_TARGET_HPP_
#define _OPENGL_RENDER_TARGET_HPP_

#include <core/TextureBuffer.hpp>
#include <core/RenderBuffer.hpp>
#include <array>

struct OpenGLRenderTarget {

    public:
        int width ;
        int height;
        int count;
        RenderTexture * target;

    public: 
        OpenGLRenderTarget( int width , int height );
        ~OpenGLRenderTarget( );
    
    public:

        void init();
        void bind( );
        void unBind( );
        void dispose( );


};


#endif