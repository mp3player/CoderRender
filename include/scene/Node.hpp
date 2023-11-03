#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include<unordered_map>
#include<component/Component.hpp>
#include <scene/Layer.hpp>



struct Component ;

struct Node : Ref {

    public:
        std::vector< Node * > children;
        Layer layer;

    private:

        std::string name;
        std::unordered_map< std::string , Component *> components;

    public:

        explicit Node(  );
        ~Node();

    public:

        void setName( std::string );

        std::string getName() const ;

        void addComponent( Component * component );

        bool hasComponent( std::string name );

        Component * findComponent( std::string name );
        
        Component * removeComponent( std::string name );

    private:

        void dispose();

    public:

        void update( float deltaTime );

};

#endif