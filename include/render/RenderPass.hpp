#ifndef _RENDER_PASS_HPP_
#define _RENDER_PASS_HPP_

#include <core/RenderBuffer.hpp>
#include <scene/Scene.hpp>
#include <render/OpenGLRenderTarget.hpp>
#include <render/OpenGLRenderer.hpp>
#include <render/Pass.hpp>

struct RenderPass : Pass {

    public:

        int width ; 
        int height ;

    public:

        FrameBuffer * frameBuffer;
        RenderBuffer * depthBuffer;
        RenderTexture * renderTexture;

    public:

        RenderPass( int width , int height );
        ~RenderPass();

    public:

        void init() ;
        void dispose();
        void render();


};





#endif