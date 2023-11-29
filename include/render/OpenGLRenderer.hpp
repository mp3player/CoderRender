#ifndef _OPENGL_RENDERER_HPP_
#define _OPENGL_RENDERER_HPP_


#include <render/Renderer.hpp>
#include <opengl/shader/OpenGLProgram.hpp>
#include <core/VertexBuffer.hpp>
#include <core/TextureBuffer.hpp>

#include <render/OpenGLRenderTarget.hpp>
#include <core/OpenGLState.hpp>


Program * getProgram( Node * node );

VertexArrayBuffer * getVAO( Node * node );

TextureBuffer * getTexture( Texture * texture );


struct OpenGLRenderer : Renderer {

    public:
    
        OpenGLState state = OpenGLState();

    public:
    
        OpenGLRenderer();
        ~OpenGLRenderer();

    public:

        void setColor( float r , float g , float b );
        void setColor( glm::vec3 color );
        void setAlpha( float alpha );

        void enable( );
        void disable();
    
    public:

        void clearColorBuffer();
        void clearDepthBuffer();
        void clearStencilBuffer();
        
    public:

        void clear( unsigned int mask ) override ;
        void render( Scene * scene ) override ;

    public:

        void renderShadow( Scene * scene );


    private:

        void setCamera( Program * program , Node * camera );

        void setAmbientLight( Program * program , std::vector< Node * > ambients );

        void setDirectionalLight( Program * program , std::vector< Node * > directionals );

        void setSpotLight( Program * program , std::vector< Node * > spots );

        void setPointLight( Program * program , std::vector< Node * > points );

        void setRenderParameter( Program * program , RenderComponent * parameters );


};







#endif