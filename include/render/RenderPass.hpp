#ifndef _RENDER_PASS_HPP_
#define _RENDER_PASS_HPP_

#include <core/RenderBuffer.hpp>
#include <scene/Scene.hpp>



struct RenderPass {

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


};


#endif