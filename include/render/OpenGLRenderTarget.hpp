#ifndef _OPENGL_RENDER_TARGET_HPP_
#define _OPENGL_RENDER_TARGET_HPP_

#include <core/TextureBuffer.hpp>
#include <core/RenderBuffer.hpp>

struct OpenGLRenderTarget {

    public:
        std::unordered_map< int , RenderTexture * > targets;

    

};


#endif