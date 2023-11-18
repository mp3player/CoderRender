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
        void bind( GLenum target ) override;
        void unBind() override;
        void dispose() override;


    public:
        void bind() ;
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
        void bind( GLenum target ) override;
        void unBind() override;
        void dispose() override;

    public:
        void bind();



};


struct FrameBuffer : Buffer {

    public:
        int width;
        int height;

    public:
        FrameBuffer( int width , int height );

    public:
        void init() override;
        void bind( GLenum target ) override;
        void unBind() override;
        void dispose() override;

    public:
        void bind() ;

};
