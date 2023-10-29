#include <scene/Node.hpp>
#include <glad/glad.h>



// Entity
Node::Node( std::string name ) : name( name ){}

Node::~Node(){
    
}

std::string Node::getName() const {
    return this->name;
}

void Node::addComponent( Component * component ){

    if( this->components.find( component->getName() ) == this->components.end() ){
        this->components.emplace( component->getName() , component );
    }

}

bool Node::hasComponent( std::string name ){
    return ( this->components.find( name ) != this->components.end() );
}

Component * Node::findComponent( std::string name ){

    if( this->components.find( name ) == this->components.end() ){
        return nullptr;
    }

    return this->components.at( name );

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

void Node::dispose(){
    
    // delete component
    auto begin = this->components.begin() , end = this->components.end();
    while( begin != end ){
        Component * component = begin->second;
        delete component;
        begin ++;
    }

}


