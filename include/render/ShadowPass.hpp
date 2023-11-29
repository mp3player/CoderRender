#ifndef _PASS_SHADOW_HPP_
#define _PASS_SHADOW_HPP_

#include <render/Pass.hpp>
#include <scene/Scene.hpp>



struct ShadowPass : Pass {

    public:

        Program * shadowProgram = nullptr ;
        FrameBuffer * frameBuffer = nullptr ;
        std::unordered_map< Node * , RenderTexture * > shadowMaps;
        RenderBuffer * depthBuffer = nullptr ;

    public:

        ShadowPass( int width , int height );
        ~ShadowPass();

    public:

        void dispose( );
        void render( Scene * scene );

};


#endif 