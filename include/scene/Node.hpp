#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include<unordered_map>
#include<component/Component.hpp>
#include <scene/Layer.hpp>
#include <core/Log.hpp>



struct Component ;

struct Node : Ref {

    public:
    
        Node * parent = nullptr;
        std::vector< Node * > children;
        Layer layer;

    private:

        std::string name;
        std::unordered_map< std::string , Component *> components;

    public:

        explicit Node(  );
        ~Node();

    public:

        void addChild( Node * node );

        void setName( std::string );

        std::string getName() const ;

    public:

        void addComponent( Component * component );
        
        Component * removeComponent( std::string name );

        template< typename T >
        bool hasComponent();

        template< typename T >
        T * getComponent( );

        template< typename T >
        std::vector< T * > getComponents();

    public:

        template< typename T >
        Node * findChildWithComponent();

        template< typename T >
        std::vector< Node * > findChildrenWithComponent();

    private:

        void dispose();

    public:

        void update( float deltaTime );

};


template< typename T >
bool Node::hasComponent(){

    T * comp = this->getComponent<T>();
    return comp != nullptr ;

}

template< typename T >
T * Node::getComponent( ){

    auto begin = this->components.begin() , end = this->components.end();

    while( begin != end ){

        T * comp = dynamic_cast< T * >( begin->second );
        if( comp ){
            return comp;
        }

        begin ++;

    }

    return nullptr;
}

template< typename T >
std::vector< T * > Node::getComponents(){

    std::vector< T * > comps;
    
    auto begin = this->components.begin() , end = this->components.end();

    while( begin != end ){

        T * comp = dynamic_cast< T * >( begin->second );

        if( comp ){
            comps.push_back( comps );
        }

        begin ++;

    }

    return comps;
}

template< typename T >
Node * Node::findChildWithComponent(){
    
    std::vector< Node * > node = this->findChildrenWithComponent<T>();

    if( node.size() > 0 ) return node.at( 0 );

    return nullptr;

}

template< typename T >
std::vector< Node * > Node::findChildrenWithComponent(){

    std::vector< Node * > nodes;
    for( Node * node : this->children ){
        
        if( node->hasComponent<T>() ) {
            nodes.push_back( node );
        }

        std::vector< Node * > _nodes = node->findChildrenWithComponent<T>();
        nodes.insert( nodes.end() , _nodes.begin() , _nodes.end() );

    }

    // Log::cout( __FILE__ , nodes.size() );
    
    return nodes;

}







#endif