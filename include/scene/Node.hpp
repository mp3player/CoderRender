#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include<unordered_map>
#include<component/Component.hpp>
#include <scene/Layer.hpp>

static int entity_version = 0;

struct Component ;

struct Node : Ref {

    public:
        std::vector< Node * > children;

    private:

        std::string name;
        
        std::unordered_map< std::string , Component *> components;
        Layer layer;

    public:

        explicit Node( std::string name = "DefaultNode_" + entity_version );
        ~Node();

    public:

        std::string getName() const ;

        void addComponent( Component * component );

        bool hasComponent( std::string name );

        Component * findComponent( std::string name );
        
        Component * removeComponent( std::string name );

    private:
        void dispose();

};

#endif