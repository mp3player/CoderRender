#ifndef _RENDER_BUFFER_HPP_
#define _RENDER_BUFFER_HPP_

#include <core/Buffer.hpp>


struct RenderBuffer : Buffer {

    public:
        int width;
        int height;
        
    public:
        GLenum component;

    public:
        RenderBuffer( int width , int height );

    public:
        void init() override;
        void bind() override;
        void unBind() override;
        void dispose() override;


    public:
        void allocate( GLenum format );

};

struct RenderTexture : Buffer {

    public:
        int width;
        int height;

    public:
        RenderTexture( int width , int height );

    public:
        void init() override;
        void bind() override;
        void unBind() override;
        void dispose() override;



};


struct FrameBuffer : Buffer {

    public:
        int width;
        int height;

    public:
        FrameBuffer( int width , int height );

    public:
        void init() override;
        void bind() override;
        void unBind() override;
        void dispose() override;

    public:
        void bindRenderBuffer( RenderBuffer * renderBuffer , GLenum format , GLenum attachment );
        void bindRenderTexture( RenderTexture * texture , GLenum attachment , int level );
        void drawBuffer( std::vector< GLenum > attachments );
        void copy( FrameBuffer * destination , int sx , int sy , int sw , int sh , int dx , int dy , int dw , int dh , unsigned char mask , unsigned int filter );

};


#endif