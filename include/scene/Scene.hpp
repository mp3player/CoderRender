#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <core/MemoryManager.hpp>
#include <scene/Node.hpp>

typedef MemoryManager< Node > NodeManager;

struct Scene : Node {

    private:

        NodeManager _nodes;

    public:

        template< typename T >
        std::vector< Node * > findWithComponent();


};




#endif
