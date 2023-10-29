#include <scene/Scene.hpp>

Scene::~Scene(){


    auto release = []( Node * node ){
        if( node != nullptr ){
            delete node;
        }
    };

    for( Node * node : this->children ){
        release( node );
    }

}