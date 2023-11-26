#ifndef _OPENGL_RENDERER_HPP_
#define _OPENGL_RENDERER_HPP_


#include <render/Renderer.hpp>
#include <opengl/shader/OpenGLProgram.hpp>
#include <core/VertexBuffer.hpp>
#include <core/TextureBuffer.hpp>
#include <scene/Scene.hpp>


Program * getProgram( Node * node );

VertexArrayBuffer * getVAO( Node * node );

TextureBuffer * getTexture( Texture * texture );


struct OpenGLRenderer : Renderer {

    public:

        glm::vec3 color = { 0.0f , 0.0f , 0.0f };
        float alpha = 0.2f ;

    public:
    
        OpenGLRenderer();
        ~OpenGLRenderer();

    public:

        void enable( );
        void disable();
        void clear() override ;

    private:

        void setCamera( Program * program , Node * camera );

        void setAmbientLight( Program * program , std::vector< Node * > ambients );

        void setDirectionalLight( Program * program , std::vector< Node * > directionals );

        void setSpotLight( Program * program , std::vector< Node * > spots );

        void setPointLight( Program * program , std::vector< Node * > points );

        void setRenderParameter( Program * program , RenderComponent * parameters );
    
    public:

        void render( Scene * scene ) ;

};




#endif