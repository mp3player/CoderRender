#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <scene/Node.hpp>

struct Scene {

    std::vector< Node * > children;

    public:
        ~Scene();

};




#endif
