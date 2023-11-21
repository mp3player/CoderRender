#include <scene/Node.hpp>
#include <glad/glad.h>
#include <component/Transform.hpp>

static int entity_version = 0;

// Entity
Node::Node(  ) : name( "DefaultNode_" + std::to_string( entity_version ) ){
    entity_version += 1;
    this->addComponent( new Transform() );
}

Node::~Node(){
    this->dispose();
}

void Node::addChild( Node * node ){

    assert( node != nullptr );
    this->children.push_back( node );
    node->parent = this;
    
}

void Node::setName( std::string name ) {
    this->name = name;
}

std::string Node::getName() const {
    return this->name;
}

void Node::addComponent( Component * component ){

    assert( component != nullptr );
    this->components.push_back( component );
    component->setNode( this );

}

void Node::update( float deltaTime ){


    std::vector< Component * >::iterator begin = this->components.begin(),
    end = this->components.end();

    while( begin < end ){
        
        Component * component = *begin;
        component->update( deltaTime );
        begin++;

    }
    

}

void Node::dispose(){

    int k = 0;
    auto begin = this->components.begin() , end = this->components.end();
    while( begin < end ){
        
        Component * component = *begin;
        delete component;
        begin ++;
    }

    for( Node * node : this->children ){
        delete node;
    }

    this->children.clear();

}

