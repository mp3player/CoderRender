#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <core/MemoryManager.hpp>
#include <scene/Node.hpp>

typedef MemoryManager< Node > NodeManager;

#include <scene/Node.hpp>

struct Scene {

    private:

        NodeManager _nodes;

    public:

        std::vector< Node * > children;

    public:

        ~Scene();

};




#endif
