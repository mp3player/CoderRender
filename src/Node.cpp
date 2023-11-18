#include <scene/Node.hpp>
#include <glad/glad.h>

static int entity_version = 0;

// Entity
Node::Node(  ) : name( "DefaultNode_" + std::to_string( entity_version ) ){
    entity_version += 1;
    this->addComponent( new Transform() );
}

Node::~Node(){
    
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
    if( this->components.find( component->getName() ) == this->components.end() ){
        this->components.emplace( component->getName() , component );
        component->setNode( this );
    }
    

}

Component * Node::removeComponent( std::string name ){

    if( this->components.find( name ) == this->components.end() ){
        return nullptr;
    }
    auto iter = this->components.find( name );
    Component * component = iter->second;

    // this function will cause the iter become invalid => the content need to store
    this->components.erase( iter );

    return component;

}

void Node::update( float deltaTime ){


#define Iterator std::unordered_map< std::string , Component * >::iterator 

    Iterator begin = this->components.begin();
    Iterator end = this->components.end();

    while( begin != end ){
        
        Component * component = begin->second;
        component->update( deltaTime );
        begin++;

    }
    

}

void Node::dispose(){
    
    // delete component
    auto begin = this->components.begin() , end = this->components.end();
    while( begin != end ){
        Component * component = begin->second;
        delete component;
        begin ++;
    }

}

