#ifndef _COMPONENT_MESH_RENDERER_HPP_
#define _COMPONENT_MESH_RENDERER_HPP_

#include <glm/glm.hpp>
#include <scene/Scene.hpp>


struct Renderer {

    public:
        int x , y , width , height ;
        glm::vec3 color = glm::vec3( 0.0f );
        float alpha = 1.0f ;

        int multiSample = 1;
        bool antialias = true;

    public:
        virtual ~Renderer();

    public:
        virtual void setColor( float r , float g , float b );
        virtual void setColor( glm::vec3 color );
        virtual void setAlpha( float a );

        virtual void clear( unsigned int mask ) = 0;
        virtual void render( Scene * scene ) = 0;

};



#endif 