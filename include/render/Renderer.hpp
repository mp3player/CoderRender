#ifndef _COMPONENT_MESH_RENDERER_HPP_
#define _COMPONENT_MESH_RENDERER_HPP_

#include <scene/Node.hpp>



struct Renderer {

    public:

        glm::vec3 clearColor = glm::vec3( 0.0f );

    public:
        virtual ~Renderer();

    public:

        virtual void clear() = 0;

};



#endif 