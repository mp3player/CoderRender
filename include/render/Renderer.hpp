#ifndef _COMPONENT_MESH_RENDERER_HPP_
#define _COMPONENT_MESH_RENDERER_HPP_

#include <core/VertexBuffer.hpp>
#include <core/TextureBuffer.hpp>
#include <scene/Node.hpp>
#include <core/MemoryManager.hpp>
#include <scene/Scene.hpp>
#include <component/Camera.hpp>



struct Renderer {

    public:

        glm::vec3 clearColor = glm::vec3( 0.0f );
        float clearAlpha = 1.0f ;
        bool depthTest = true;
        bool alphaTest = false;


    public:
        Renderer();
        ~Renderer();

    public:

        void clear();
        void render( Scene * scene );

};

Program * getProgram( Node * node );
VertexArrayBuffer * getVAO( Node * node );

#endif 